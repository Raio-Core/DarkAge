# DA

> An Unreal Engine 5.7 Project | Version 0.4.0 alpha

<!-- BADGES_START -->
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-0EBEED?logo=unrealengine&logoColor=white)](https://www.unrealengine.com/)
[![Version](https://img.shields.io/badge/Version-0.4.0-orange)]()
[![Stage](https://img.shields.io/badge/Stage-alpha-orange)]()
[![Build](https://img.shields.io/badge/Build-68-blue)]()
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
<!-- BADGES_END -->

<!-- VERSION_START -->
## Version Information

| Property | Value |
|----------|-------|
| **Version** | `0.4.0` |
| **Stage** | `alpha` |
| **Build** | `68` |
| **Full Version** | `v0.4.0-alpha+build.68` |

### Development Progress

Core features complete, testing in progress

| Metric | Count |
|--------|-------|
| Breaking Changes | 0 |
| New Features | 12 |
| Bug Fixes | 3 |
| Other Changes | 40 |

<!-- VERSION_END -->

## Overview

<!-- DESCRIPTION_START -->
DA is an Unreal Engine project featuring a comprehensive Gameplay Ability System (GAS) with 
custom attributes (Health, Stamina, Mana), character mechanics, and modular architecture designed for extensibility.

### Key Features

- Gameplay Ability System - Full GAS integration with custom ability system component
- Attribute System - Replicated attributes for Health, Stamina, and Mana
- Character Classes - Flexible character class system with data-driven configuration
- State Tree - AI and gameplay logic using Unreal's StateTree plugin
- Modular Architecture - Clean separation of systems for maintainability
<!-- DESCRIPTION_END -->

<!-- STATS_START -->
## Project Statistics

| Metric | Count |
|--------|-------|
| Header Files | 30 |
| Source Files | 30 |
| Total C++ Files | 60 |
| Total Lines | 2,952 |
| Code Lines | 2,768 |
| Comment Lines | 184 |
| Total Commits | 55 |
| Contributors | 3 |

<!-- STATS_END -->

<!-- COPYRIGHT_START -->
## Copyright

Copyright 2026 RaioCore and Raioix. All Rights Reserved.

### Copyright Holders

| Holder | Role |
|--------|------|
| RaioCore | Project Owner |
| Raioix | Project Owner |

### File Copyright Status

| Status | Count |
|--------|-------|
| Correct Copyright | 60 |
| Epic Games (Template) | 0 |
| Placeholder | 0 |
| Missing | 0 |

<!-- COPYRIGHT_END -->

<!-- DIRECTORY_START -->
## Project Structure

```
Source/
    DA/
        Private/
            Actors/
                EffectActor.cpp
            Character/
                CharacterBasse.cpp
                DACharacter.cpp
                EnemyBasse.cpp
            Data/
                CharacterClassInfo.cpp
                ProjectileInfo.cpp
            Game/
                GameMode/
                    DAGameMode.cpp
                    DA_GameMode.cpp
                PlayerController/
                    DAPlayerController.cpp
                    DA_PlayerController.cpp
                PlayerState/
                    DAPlayerState.cpp
            Input/
                DAInputConfig.cpp
                DASystemsInputComponent.cpp
            Interfaces/
                DAAbilitySystemInterface.cpp
                InventoryInterface.cpp
            Projectiles/
                ProjectileBase.cpp
            Systems/
                AbilitySystem/
                    Abilities/
                        DADamageAbility.cpp
                        DAGameplayAbility.cpp
                        ProjectileAbility.cpp
                    Attributes/
                        DAAttributeSet.cpp
                    Libraries/
                        DAAbilitySystemLibrary.cpp
                    DAAbilitySystemComponent.cpp
                Inventory/
                    InventoryComponent.cpp
                    ItemTypes.cpp
                    ItemTypesToTables.cpp
                DAAbilityTypes.cpp
            UI/
                WidgetControllers/
                    InventoryWidgetController.cpp
                    WidgetController.cpp
                DASystemsWidget.cpp
        Public/
            Actors/
                EffectActor.h
            Character/
                CharacterBasse.h
                DACharacter.h
                EnemyBasse.h
            Data/
                CharacterClassInfo.h
                ProjectileInfo.h
            Game/
                GameMode/
                    DAGameMode.h
                    DA_GameMode.h
                PlayerController/
                    DAPlayerController.h
                    DA_PlayerController.h
                PlayerState/
                    DAPlayerState.h
            Input/
                DAInputConfig.h
                DASystemsInputComponent.h
            Interfaces/
                DAAbilitySystemInterface.h
                InventoryInterface.h
            Projectiles/
                ProjectileBase.h
            Systems/
                AbilitySystem/
                    Abilities/
                        DADamageAbility.h
                        DAGameplayAbility.h
                        ProjectileAbility.h
                    Attributes/
                        DAAttributeSet.h
                    Libraries/
                        DAAbilitySystemLibrary.h
                    DAAbilitySystemComponent.h
                Inventory/
                    InventoryComponent.h
                    ItemTypes.h
                    ItemTypesToTables.h
                DAAbilityTypes.h
            UI/
                WidgetControllers/
                    InventoryWidgetController.h
                    WidgetController.h
                DASystemsWidget.h
        DA.Build.cs
        DA.cpp
        DA.h
    DA.Target.cs
    DAEditor.Target.cs
```

<!-- DIRECTORY_END -->

<!-- CLASSES_START -->
## C++ Classes

### DA

| Class | Type | Base | Description |
|-------|------|------|-------------|
| `ACharacterBasse` | Class | `ACharacter` |  |
| `ADACharacter` | Class | `ACharacterBasse` |  |
| `ADAGameMode` | Class | `AGameModeBase` |  |
| `ADAPlayerController` | Class | `APlayerController` |  |
| `ADAPlayerState` | Class | `APlayerState` |  |
| `ADA_GameMode` | Class | `AGameMode` |  |
| `ADA_PlayerController` | Class | `APlayerController` |  |
| `AEffectActor` | Class | `AActor` |  |
| `AEnemyBasse` | Class | `ACharacterBasse` |  |
| `AProjectileBase` | Class | `AActor` |  |
| `FCharacterClassDefaultInfo` | Struct | `-` |  |
| `FConsumableProps` | Struct | `-` |  |
| `FDAInputAction` | Struct | `-` |  |
| `FDamageEffectInfo` | Struct | `-` |  |
| `FMasterItemDefinition` | Struct | `-` |  |
| `FPackagedInventory` | Struct | `-` |  |
| `FProjectileParams` | Struct | `-` |  |
| `UCharacterClassInfo` | Class | `UDataAsset` |  |
| `UDAAbilitySystemComponent` | Class | `UAbilitySystemComponent` |  |
| `UDAAbilitySystemLibrary` | Class | `UBlueprintFunctionLibrary` |  |
| `UDAAttributeSet` | Class | `UAttributeSet` |  |
| `UDADamageAbility` | Class | `UDAGameplayAbility` |  |
| `UDAGameplayAbility` | Class | `UGameplayAbility` |  |
| `UDAInputConfig` | Class | `UDataAsset` |  |
| `UDASystemsWidget` | Class | `UUserWidget` |  |
| `UInventoryWidgetController` | Class | `UWidgetController` |  |
| `UItemTypesToTables` | Class | `UDataAsset` |  |
| `UProjectileAbility` | Class | `UDADamageAbility` |  |
| `UProjectileInfo` | Class | `UDataAsset` |  |
| `UWidgetController` | Class | `UObject` |  |

<!-- CLASSES_END -->

<!-- TAGS_START -->
## Gameplay Tags

### Character
- `Character.Enemy.Primary`
- `Character.Player.Default`

### Input
- `Input.DynamicProjectileAbility`
- `Input.EAbility`
- `Input.QAbility`
- `Input.ShiftAbility`

### Item
- `Item.Consumable.HealthPotion`
- `Item.Consumable.ManaPotion`

### Projectile
- `Projectile.Basic.Type1`
- `Projectile.Basic.Type2`

<!-- TAGS_END -->

<!-- COMMITS_START -->
## Recent Changes

- [`f178451`](https://github.com/Raio-Core/DarkAge/commit/f1784519d2cfefc8eae4467dfcc1ab181d0c908d) Merge remote-tracking branch 'origin/main' (2026-03-11)
- [`8ff5868`](https://github.com/Raio-Core/DarkAge/commit/8ff5868464c5bc4fea31338000073ab5a86b61c4) feat(abilities): implement projectile damage application sys... (2026-03-11)
- [`92540fa`](https://github.com/Raio-Core/DarkAge/commit/92540fab5b7417dc48b5de763dc3d2d5fdd5aa01) docs: auto-update README [skip ci] (2026-03-09)
- [`1e9637e`](https://github.com/Raio-Core/DarkAge/commit/1e9637e51dcac3c655fede51810cd23743bec73b) Merge remote-tracking branch 'origin/main' (2026-03-09)
- [`04a15e3`](https://github.com/Raio-Core/DarkAge/commit/04a15e39a0c9cd3da59af4d7923cf3f7f16a93e3) Merge branch 'PRJ2' (2026-03-09)
- [`94b7d0d`](https://github.com/Raio-Core/DarkAge/commit/94b7d0dc6986571ef2d9f8fe7b087b8d74baee1f) o Created Dynamic Projectile o Created 2 versions (2026-03-09)
- [`221a32a`](https://github.com/Raio-Core/DarkAge/commit/221a32a04f9bfcb65fe09c7f98f38b6503f8b753) Merge branch 'Feature/Projectile2' into PRJ2 (2026-03-09)
- [`0788f68`](https://github.com/Raio-Core/DarkAge/commit/0788f682bbcf795509428075783ca098adc37492) Merge branch 'Feature/Projectile2' (2026-03-09)
- [`494079d`](https://github.com/Raio-Core/DarkAge/commit/494079db5257fe299f3c0346e408714b0ad3e3a5) docs: auto-update README [skip ci] (2026-03-08)
- [`8c28d43`](https://github.com/Raio-Core/DarkAge/commit/8c28d436a818a67bba6f9fe1ca3f1e01ec531fbc) chore(config): optimize engine streaming and garbage collect... (2026-03-04)

<!-- COMMITS_END -->

<!-- CONTRIBUTORS_START -->
## Contributors

- **Raio-Core** (41 commits)
- **github-actions[bot]** (12 commits)
- **Raioix** (2 commits)

<!-- CONTRIBUTORS_END -->

---

<p align="center">
  <i>Copyright 2026 RaioCore and Raioix. All Rights Reserved.</i><br><br>
  <i>Last updated: 2026-03-11 23:34:38 UTC</i><br>
  <i>This README is automatically generated from project files and git history.</i><br>
  <i>Version follows semantic versioning based on conventional commits.</i>
</p>
