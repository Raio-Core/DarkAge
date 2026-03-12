# ADACharacter

*A simple player-controllable third person character Implements a controllable orbiting camera*

**File:** `Source\DA\Public\Character\DACharacter.h`

## Inheritance

```
ACharacterBasse -> IAbilitySystemInterface -> IDAAbilitySystemInterface -> ADACharacter
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
| `TObjectPtr<USceneComponent>` | `)` | VisibleAnywhere | meta | - |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |
| `unknown` | `UInputAction*` | EditAnywhere | `Input` |

## Functions

| Name | Return Type | Parameters | Specifiers |
|------|-------------|------------|------------|
| `DoMove` | `virtual void` | `float Right, float Forward` | BlueprintCallable |
| `DoLook` | `virtual void` | `float Yaw, float Pitch` | BlueprintCallable |
| `DoJumpStart` | `virtual void` | - | BlueprintCallable |
| `DoJumpEnd` | `virtual void` | - | BlueprintCallable |
