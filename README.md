# DA

> An Unreal Engine 5.7 Project | Version 0.4.0 alpha

<!-- BADGES_START -->
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-0EBEED?logo=unrealengine&logoColor=white)](https://www.unrealengine.com/)
[![Version](https://img.shields.io/badge/Version-0.4.0-orange)]()
[![Stage](https://img.shields.io/badge/Stage-alpha-orange)]()
[![Build](https://img.shields.io/badge/Build-54-blue)]()
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
<!-- BADGES_END -->

<!-- VERSION_START -->
## Version Information

| Property | Value |
|----------|-------|
| **Version** | `0.4.0` |
| **Stage** | `alpha` |
| **Build** | `54` |
| **Full Version** | `v0.4.0-alpha+build.54` |

### Development Progress

Core features complete, testing in progress

| Metric | Count |
|--------|-------|
| Breaking Changes | 0 |
| New Features | 10 |
| Bug Fixes | 2 |
| Other Changes | 29 |

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
| Header Files | 29 |
| Source Files | 29 |
| Total C++ Files | 58 |
| Total Lines | 2,715 |
| Code Lines | 2,539 |
| Comment Lines | 176 |
| Total Commits | 41 |
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
| Correct Copyright | 58 |
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
| `FMasterItemDefinition` | Struct | `-` |  |
| `FPackagedInventory` | Struct | `-` |  |
| `FProjectileParams` | Struct | `-` |  |
| `UCharacterClassInfo` | Class | `UDataAsset` |  |
| `UDAAbilitySystemComponent` | Class | `UAbilitySystemComponent` |  |
| `UDAAbilitySystemLibrary` | Class | `UBlueprintFunctionLibrary` |  |
| `UDAAttributeSet` | Class | `UAttributeSet` |  |
| `UDAGameplayAbility` | Class | `UGameplayAbility` |  |
| `UDAInputConfig` | Class | `UDataAsset` |  |
| `UDASystemsWidget` | Class | `UUserWidget` |  |
| `UInventoryWidgetController` | Class | `UWidgetController` |  |
| `UItemTypesToTables` | Class | `UDataAsset` |  |
| `UProjectileAbility` | Class | `UDAGameplayAbility` |  |
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

- [`19f48bf`](https://github.com/Raio-Core/DarkAge/commit/19f48bfb9b683dac58526f5629fc7bae848c797a) Merge remote-tracking branch 'origin/main' (2026-02-28)
- [`556be2f`](https://github.com/Raio-Core/DarkAge/commit/556be2f36947d4ce2d35b3dfdc210658ed034acb) feat(projectile-system): Implement networked projectile abil... (2026-02-28)
- [`32dd2f1`](https://github.com/Raio-Core/DarkAge/commit/32dd2f12668bd25cc2180c1a06d876794be1ff1a) docs: auto-update README [skip ci] (2026-02-28)
- [`4bf1872`](https://github.com/Raio-Core/DarkAge/commit/4bf187232d3928e61545bf3985e68f812a33b38b) feat(character): add network replication for enemy attribute... (2026-02-28)
- [`992f2ac`](https://github.com/Raio-Core/DarkAge/commit/992f2ac9c8f24c9afa7c7084bda3555cbd8d9703) Merge remote-tracking branch 'origin/main' (2026-02-27)
- [`d66d2a6`](https://github.com/Raio-Core/DarkAge/commit/d66d2a6783301be53cbd69be27d178d30691e87e) docs(readme): overhaul readme with game overview and docs (2026-02-27)
- [`ed70ff8`](https://github.com/Raio-Core/DarkAge/commit/ed70ff88a127cfc169d2df1b3945351046b5c0a3) docs: auto-update README [skip ci] (2026-02-28)
- [`a2366f5`](https://github.com/Raio-Core/DarkAge/commit/a2366f5c79123cb12abf973addf3a681cbb90fd4) Merge remote-tracking branch 'origin/main' (2026-02-27)
- [`a49e3a0`](https://github.com/Raio-Core/DarkAge/commit/a49e3a0e3f371d95b3cdeff10976fdad44b4efa6) feat: add gameplay tags for character types and ability inpu... (2026-02-27)
- [`fdd11e1`](https://github.com/Raio-Core/DarkAge/commit/fdd11e1646f9a7b73d72c4e01a94b7ddf6818d6c) docs: auto-update README [skip ci] (2026-02-28)

<!-- COMMITS_END -->

<!-- CONTRIBUTORS_START -->
## Contributors

- **Raio-Core** (31 commits)
- **github-actions[bot]** (8 commits)
- **Raioix** (2 commits)

<!-- CONTRIBUTORS_END -->

---

<p align="center">
  <i>Copyright 2026 RaioCore and Raioix. All Rights Reserved.</i><br><br>
  <i>Last updated: 2026-03-01 01:34:43 UTC</i><br>
  <i>This README is automatically generated from project files and git history.</i><br>
  <i>Version follows semantic versioning based on conventional commits.</i>
</p>
