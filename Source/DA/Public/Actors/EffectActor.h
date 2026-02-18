// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UGameplayEffect;
class UBoxComponent;

UCLASS()
class DA_API AEffectActor : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> ActorMesh;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> OverlapBox;
	
	UPROPERTY(EditAnywhere, Category="Custom Values|Effects")
	TSubclassOf<UGameplayEffect> OverlapEffect;
	
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:

	AEffectActor();
	
	
};
