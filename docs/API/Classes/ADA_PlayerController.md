# ADA_PlayerController

*PlayerController with inventory and input mapping support*

**File:** `Source\DA\Public\Game\PlayerController\DA_PlayerController.h`

## Inheritance

```
APlayerController -> IAbilitySystemInterface -> IInventoryInterface -> IDAAbilitySystemInterface -> ADA_PlayerController
```

## Properties

| Name | Type | Specifiers | Category |
|------|------|------------|----------|
| `unknown` | `TObjectPtr<UDAAbilitySystemComponent>` | - | - |
| `unknown` | `TObjectPtr<UDAInputConfig>` | EditDefaultsOnly | `Custom Values|Input` |
| `TObjectPtr<UInventoryComponent>` | `, Replicated)` | VisibleAnywhere | BlueprintReadOnly | meta | - |
| `unknown` | `TObjectPtr<UInventoryWidgetController>` | - | - |
| `unknown` | `TSubclassOf<UInventoryWidgetController>` | EditDefaultsOnly | `Custom Values|Widgets` |
| `TObjectPtr<UDASystemsWidget>` | `)` | BlueprintReadOnly | meta | - |
| `unknown` | `TSubclassOf<UDASystemsWidget>` | EditDefaultsOnly | `Custom Values|Widgets` |
| `unknown` | `TArray<UInputMappingContext*>` | EditAnywhere | `Input|Input Mappings` |
| `unknown` | `TArray<UInputMappingContext*>` | EditAnywhere | `Input|Input Mappings` |
| `unknown` | `TSubclassOf<UUserWidget>` | EditAnywhere | `Input|Touch Controls` |
| `unknown` | `TObjectPtr<UUserWidget>` | - | - |
| `=` | `bool bForceTouchControls` | EditAnywhere | Config | `Input|Touch Controls` |

## Functions

| Name | Return Type | Parameters | Specifiers |
|------|-------------|------------|------------|
| `CreateInventoryWidget` | `void` | - | BlueprintCallable |
