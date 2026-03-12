# ADAPlayerState

**File:** `Source\DA\Public\Game\PlayerState\DAPlayerState.h`

## Inheritance

```
APlayerState -> IAbilitySystemInterface -> ADAPlayerState
```

## Properties

| Name | Type | Specifiers | Category |
|------|------|------------|----------|
| `TObjectPtr<UDAAbilitySystemComponent>` | `)` | VisibleAnywhere | BlueprintReadOnly | meta | - |
| `TObjectPtr<UDAAttributeSet>` | `)` | BlueprintReadOnly | meta | - |

## Functions

| Name | Return Type | Parameters | Specifiers |
|------|-------------|------------|------------|
| `GetDAAbilitySystemComponent` | `UDAAbilitySystemComponent*` | - | BlueprintPure |
| `GetDAAttributes` | `UDAAttributeSet*` | - | BlueprintPure |
