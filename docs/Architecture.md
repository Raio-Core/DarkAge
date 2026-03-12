# Architecture Overview

This document provides a high-level overview of the DA project's architecture.

## System Architecture

```mermaid
classDiagram
    AActor <|-- AEffectActor
    ACharacter <|-- ACharacterBasse
    ACharacterBasse <|-- ADACharacter
    IAbilitySystemInterface <|-- ADACharacter
    IDAAbilitySystemInterface <|-- ADACharacter
    ACharacterBasse <|-- AEnemyBasse
    IAbilitySystemInterface <|-- AEnemyBasse
    UDataAsset <|-- UCharacterClassInfo
    UDataAsset <|-- UProjectileInfo
    UDataAsset <|-- UDAInputConfig
    AActor <|-- AProjectileBase
    UUserWidget <|-- UDASystemsWidget
    AGameModeBase <|-- ADAGameMode
    AGameMode <|-- ADA_GameMode
    APlayerController <|-- ADAPlayerController
    APlayerController <|-- ADA_PlayerController
    IAbilitySystemInterface <|-- ADA_PlayerController
    IInventoryInterface <|-- ADA_PlayerController
    IDAAbilitySystemInterface <|-- ADA_PlayerController
    APlayerState <|-- ADAPlayerState
    IAbilitySystemInterface <|-- ADAPlayerState
    UAbilitySystemComponent <|-- UDAAbilitySystemComponent
    UDataAsset <|-- UItemTypesToTables
    UDAGameplayAbility <|-- UDADamageAbility
    UGameplayAbility <|-- UDAGameplayAbility
    UDADamageAbility <|-- UProjectileAbility
    UAttributeSet <|-- UDAAttributeSet
    UBlueprintFunctionLibrary <|-- UDAAbilitySystemLibrary
    UWidgetController <|-- UInventoryWidgetController
    UObject <|-- UWidgetController
    class AEffectActor {
        -TObjectPtr<UStaticMeshComponent>: )
        -TObjectPtr<UBoxComponent>: )
        -unknown: TSubclassOf<UGameplayEffect>
        -OnBoxBeginOverlap(...)
    }
    class ACharacterBasse {
        -unknown: FGameplayTag
        +BroadcastInitialValues()
        -OnHealthChanged(...)
        -OnStaminaChanged(...)
        -OnManaChanged(...)
    }
    class ADACharacter {
        +USpringArmComponent*: )
        +UCameraComponent*: )
        +TObjectPtr<UDAAbilitySystemComponent>: )
        +TObjectPtr<UDAAttributeSet>: )
        -TObjectPtr<USceneComponent>: )
        +DoMove(...)
        +DoLook(...)
        +DoJumpStart()
        +DoJumpEnd()
    }
    class AEnemyBasse {
        -=: bool bInitAttributes
        +TObjectPtr<UDAAbilitySystemComponent>: )
        +TObjectPtr<UDAAttributeSet>: )
        -OnRep_InitAttributes()
    }
    class UCharacterClassInfo {
        -FCharacterClassDefaultInfo>: TMap<FGameplayTag,
    }
    class UProjectileInfo {
        -unknown: TMap<FGameplayTag,FProjectileParams>
    }
    class UDAInputConfig {
        -unknown: TArray<FDAInputAction>
    }
    class AProjectileBase {
        -TObjectPtr<UStaticMeshComponent>: )
        -TObjectPtr<USphereComponent>: )
        -unknown: TObjectPtr<UProjectileMovementComponent>
        -unknown: FGameplayTag
        -unknown: TObjectPtr<UObject>
        -OnRep_ProjectileTag()
        -OnRep_ProjectileMesh()
        -OnSphereBeginOverlap(...)
    }
    class UDASystemsWidget {
        +TObjectPtr<UWidgetController>: )
        -OnWidgetControllerSet()
    }
    class ADAGameMode {
    }
    class ADA_GameMode {
        -unknown: TObjectPtr<UCharacterClassInfo>
        -unknown: TObjectPtr<UProjectileInfo>
    }
    class ADAPlayerController {
        -unknown: TArray<UInputMappingContext*>
        -unknown: TArray<UInputMappingContext*>
        -unknown: TSubclassOf<UUserWidget>
        -unknown: TObjectPtr<UUserWidget>
        -=: bool bForceTouchControls
    }
    class ADA_PlayerController {
        -unknown: TObjectPtr<UDAAbilitySystemComponent>
        -unknown: TObjectPtr<UDAInputConfig>
        +TObjectPtr<UInventoryComponent>: , Replicated)
        -unknown: TObjectPtr<UInventoryWidgetController>
        -unknown: TSubclassOf<UInventoryWidgetController>
        +CreateInventoryWidget()
    }
    class ADAPlayerState {
        +TObjectPtr<UDAAbilitySystemComponent>: )
        +TObjectPtr<UDAAttributeSet>: )
        +GetDAAbilitySystemComponent()
        +GetDAAttributes()
    }
    class UDAAbilitySystemComponent {
        -unknown: TSubclassOf<UGameplayAbility>
        -ServerSetDynamicProjectile(...)
    }
    class UItemTypesToTables {
        -TObjectPtr<UDataTable>>: TMap<FGameplayTag,
    }
    class UDADamageAbility {
        -unknown: TSubclassOf<UGameplayEffect>
        -unknown: FScalableFloat
    }
    class UDAGameplayAbility {
        -unknown: FGameplayTag
    }
    class UProjectileAbility {
        -unknown: TObjectPtr<AActor>
        -unknown: FGameplayTag
        +SpawnProjectile()
    }
    class UDAAttributeSet {
        +unknown: FGameplayAttributeData
        +unknown: FGameplayAttributeData
        +unknown: FGameplayAttributeData
        +unknown: FGameplayAttributeData
        +unknown: FGameplayAttributeData
        -OnRep_Health(...)
        -OnRep_MaxHealth(...)
        -OnRep_Stamina(...)
        -OnRep_MaxStamina(...)
        -OnRep_Mana(...)
    }
    class UDAAbilitySystemLibrary {
        +GetCharacterClassDefaultInfo(...)
        +GetProjectileInfo(...)
        +ApplyDamageEffect(...)
    }
    class UInventoryWidgetController {
        -unknown: TObjectPtr<AActor>
        -unknown: TObjectPtr<UInventoryComponent>
        -unknown: FInventoryItemSignature
        -unknown: FInventoryBroadcastComplete
        -unknown: FScrollBoxResetSignature
    }
    class UWidgetController {
    }
```

## Core Systems
