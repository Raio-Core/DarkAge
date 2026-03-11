// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
          #include "Net/UnrealNetwork.h"
//#include "Systems/DAAbilityTypes.h"
#include "AbilitySystemGlobals.h"
#include "Data/ProjectileInfo.h"
#include "Systems/AbilitySystem/Libraries/DAAbilitySystemLibrary.h"


AProjectileBase::AProjectileBase()
{

	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetIsReplicated(true);
	SetRootComponent(ProjectileMesh);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileMesh->SetCollisionObjectType(ECC_WorldDynamic);
	ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileMesh->SetIsReplicated(true);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");

	OverlapSphere = CreateDefaultSubobject<USphereComponent>("OverlapSphere");
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapSphere->SetupAttachment(GetRootComponent());
	
}

void AProjectileBase::SetProjectileParams(const FProjectileParams& Params, const FGameplayTag& InProjectileTag)
{
	// Set the tag - this will replicate to clients
	if (InProjectileTag.IsValid())
	{
		ProjectileTag = InProjectileTag;
	}
	
	// Replicate the mesh so clients can see it
	if (IsValid(Params.ProjectileMesh))
	{
		ReplicatedMesh = Params.ProjectileMesh;
	}
	
	if (IsValid(ProjectileMesh) && IsValid(Params.ProjectileMesh))
	{
		ProjectileMesh->SetStaticMesh(Params.ProjectileMesh);
	}
	
	if (IsValid(ProjectileMovementComponent))
	{
		ProjectileMovementComponent->InitialSpeed = Params.InitialSpeed;
		ProjectileMovementComponent->ProjectileGravityScale = Params.GravityScale;
		ProjectileMovementComponent->bShouldBounce = Params.bShouldBounce;
		ProjectileMovementComponent->Bounciness = Params.Bounciness;
	}
}

void AProjectileBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectileBase, ProjectileTag);
	DOREPLIFETIME(AProjectileBase, ReplicatedMesh);
}

void AProjectileBase::OnRep_ProjectileTag()
{
	// Look up params on the client using the replicated tag
	if (!HasAuthority() && ProjectileTag.IsValid())
	{
		if (UProjectileInfo* ProjectileInfo = UDAAbilitySystemLibrary::GetProjectileInfo(this))
		{
			if (const FProjectileParams* Params = ProjectileInfo->ProjectileInfoMap.Find(ProjectileTag))
			{
				SetProjectileParams(*Params);
			}
		}
	}
}

void AProjectileBase::OnRep_ProjectileMesh()
{

}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
	}
}

void AProjectileBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;
	
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor))
	{
		DamageEffectInfo.TargetASC = TargetASC;
		UDAAbilitySystemLibrary::ApplyDamageEffect(DamageEffectInfo);
		
		Destroy();
	}
}

