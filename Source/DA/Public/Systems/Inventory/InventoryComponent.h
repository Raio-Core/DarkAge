// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemTypes.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemTypesToTables;

USTRUCT()
struct FPackagedInventory
{
	GENERATED_BODY()
	
	virtual ~FPackagedInventory() = default;
	
	UPROPERTY()
	TArray<FGameplayTag> ItemTags;
	
	UPROPERTY()
	TArray<int32> ItemQuantities;
	
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);
	
};
template<>
struct TStructOpsTypeTraits<FPackagedInventory> : TStructOpsTypeTraitsBase2<FPackagedInventory>
{
	enum
	{
		WithNetSerializer = true
	};
};

DECLARE_MULTICAST_DELEGATE_OneParam(FInventoryPackagedSignature, const FPackagedInventory&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TMap<FGameplayTag, int32> InventoryTagMap;

	UPROPERTY(ReplicatedUsing=OnRep_CachedInventory)
	FPackagedInventory CashedInventory;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UItemTypesToTables> InventoryDefinitions;
	
	UFUNCTION(Server, Reliable)
	void ServerAddItem(const FGameplayTag& ItemTag, int32 NumItems);
	
	UFUNCTION(Server, Reliable)
	void ServerUseItem(const FGameplayTag& ItemTag, int32 NumItems);
	
	void PackageInventory(FPackagedInventory& OutInventory);
	
	UFUNCTION()
	void OnRep_CachedInventory();
	
protected:



public:

	UInventoryComponent();
	
	FInventoryPackagedSignature InventoryPackageDelegate;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable)
	void AddItem(const FGameplayTag& ItemTag, int32 NumItems = 1);
	
	UFUNCTION(BlueprintCallable)
	void UseItem(const FGameplayTag& ItemTag, int32 NumItems = 1);
	
	UFUNCTION(BlueprintPure)
	FMasterItemDefinition GetItemDefinitionByTag(const FGameplayTag& ItemTag) const;
	
	TMap<FGameplayTag, int32> GetInventoryTagMap();
	
	void ReconstructInventoryMap(const FPackagedInventory& Inventory);
	
};
