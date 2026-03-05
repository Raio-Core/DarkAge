// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Systems/DAAbilityTypes.h"
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
	ProjectileMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
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
	// Note: We don't set the mesh here because it's handled via SetProjectileParams
	// which is called from OnRep_ProjectileTag. Setting it here causes the ensure
	// failure because KnownStaticMesh hasn't been initialized yet.
	// The ReplicatedMesh is kept in sync with the actual mesh via SetProjectileParams.
}

