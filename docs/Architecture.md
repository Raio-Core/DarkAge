# Architecture Overview

This document provides a high-level overview of the DA project's architecture.

## System Architecture

```mermaid
classDiagram
    ACharacter <|-- ADACharacter
    IAbilitySystemInterface <|-- ADACharacter
    AGameModeBase <|-- ADAGameMode
    APlayerController <|-- ADAPlayerController
    AActor <|-- AEffectActor
    UDataAsset <|-- UCharacterClassInfo
    UDataAsset <|-- UDAInputConfig
    UUserWidget <|-- UDASystemsWidget
    AGameMode <|-- ADA_GameMode
    APlayerController <|-- ADA_PlayerController
    IAbilitySystemInterface <|-- ADA_PlayerController
    IInventoryInterface <|-- ADA_PlayerController
    APlayerState <|-- ADAPlayerState
    IAbilitySystemInterface <|-- ADAPlayerState
    UAbilitySystemComponent <|-- UDAAbilitySystemComponent
    UDataAsset <|-- UItemTypesToTables
    UGameplayAbility <|-- UDAGameplayAbility
    UAttributeSet <|-- UDAAttributeSet
    UBlueprintFunctionLibrary <|-- UDAAbilitySystemLibrary
    UWidgetController <|-- UInventoryWidgetController
    UObject <|-- UWidgetController
    class ADACharacter {
        +USpringArmComponent*: )
        +UCameraComponent*: )
        +TObjectPtr<UDAAbilitySystemComponent>: )
        +TObjectPtr<UDAAttributeSet>: )
        -unknown: FGameplayTag
        +BroadcastInitialValues()
        -OnHealthChanged(...)
        -OnStaminaChanged(...)
        -OnManaChanged(...)
        +DoMove(...)
    }
    class ADAGameMode {
    }
    class ADAPlayerController {
        -unknown: TArray<UInputMappingContext*>
        -unknown: TArray<UInputMappingContext*>
        -unknown: TSubclassOf<UUserWidget>
        -unknown: TObjectPtr<UUserWidget>
        -=: bool bForceTouchControls
    }
    class AEffectActor {
        -TObjectPtr<UStaticMeshComponent>: )
        -TObjectPtr<UBoxComponent>: )
        -unknown: TSubclassOf<UGameplayEffect>
        -OnBoxBeginOverlap(...)
    }
    class UCharacterClassInfo {
        -FCharacterClassDefaultInfo>: TMap<FGameplayTag,
    }
    class UDAInputConfig {
        -unknown: TArray<FDAInputAction>
    }
    class UDASystemsWidget {
        +TObjectPtr<UWidgetController>: )
        -OnWidgetControllerSet()
    }
    class ADA_GameMode {
        -unknown: TObjectPtr<UCharacterClassInfo>
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
    }
    class UItemTypesToTables {
        -TObjectPtr<UDataTable>>: TMap<FGameplayTag,
    }
    class UDAGameplayAbility {
        -unknown: FGameplayTag
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
