# ADACharacter

*A simple player-controllable third person character Implements a controllable orbiting camera*

**File:** `Source\DA\DACharacter.h`

## Inheritance

```
ACharacter -> IAbilitySystemInterface -> ADACharacter
```

## Specifiers

`abstract`

## Properties

| Name | Type | Specifiers | Category |
|------|------|------------|----------|
| `USpringArmComponent*` | `)` | VisibleAnywhere | BlueprintReadOnly | meta | `Components` |
| `UCameraComponent*` | `)` | VisibleAnywhere | BlueprintReadOnly | meta | `Components` |
| `TObjectPtr<UDAAbilitySystemComponent>` | `)` | BlueprintReadOnly | meta | - |
| `TObjectPtr<UDAAttributeSet>` | `)` | BlueprintReadOnly | meta | - |
| `unknown` | `FGameplayTag` | EditAnywhere | `Custom Values|Character Infop` |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |

## Functions

| Name | Return Type | Parameters | Specifiers |
|------|-------------|------------|------------|
| `BroadcastInitialValues` | `void` | - | BlueprintCallable |
| `OnHealthChanged` | `void` | `float CurrentHealth, float MaxHealth` | BlueprintImplementableEvent |
| `OnStaminaChanged` | `void` | `float CurrentStamina, float MaxStamina` | BlueprintImplementableEvent |
| `OnManaChanged` | `void` | `float CurrentMana, float MaxMana` | BlueprintImplementableEvent |
| `DoMove` | `virtual void` | `float Right, float Forward` | BlueprintCallable |
| `DoLook` | `virtual void` | `float Yaw, float Pitch` | BlueprintCallable |
| `DoJumpStart` | `virtual void` | - | BlueprintCallable |
| `DoJumpEnd` | `virtual void` | - | BlueprintCallable |
