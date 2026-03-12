# ACharacterBasse

**File:** `Source\DA\Public\Character\CharacterBasse.h`

## Inheritance

```
ACharacter -> ACharacterBasse
```

## Properties

| Name | Type | Specifiers | Category |
|------|------|------------|----------|
| `unknown` | `FGameplayTag` | EditAnywhere | `Custom Values|Character Infop` |

## Functions

| Name | Return Type | Parameters | Specifiers |
|------|-------------|------------|------------|
| `BroadcastInitialValues` | `virtual void` | - | BlueprintCallable |
| `OnHealthChanged` | `void` | `float CurrentHealth, float MaxHealth` | BlueprintImplementableEvent |
| `OnStaminaChanged` | `void` | `float CurrentStamina, float MaxStamina` | BlueprintImplementableEvent |
| `OnManaChanged` | `void` | `float CurrentMana, float MaxMana` | BlueprintImplementableEvent |
