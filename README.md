# DA

> An Unreal Engine 5.7 Project | Version 0.4.0 embryo

<!-- BADGES_START -->
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-0EBEED?logo=unrealengine&logoColor=white)](https://www.unrealengine.com/)
[![Version](https://img.shields.io/badge/Version-0.4.0-lightgrey)]()
[![Stage](https://img.shields.io/badge/Stage-pre--alpha-lightgrey)]()
[![Build](https://img.shields.io/badge/Build-36-blue)]()
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
<!-- BADGES_END -->

<!-- VERSION_START -->
## Version Information

| Property | Value |
|----------|-------|
| **Version** | `0.4.0` |
| **Stage** | `pre-alpha` |
| **Build** | `36` |
| **Full Version** | `v0.4.0-pre-alpha+build.36` |

### Development Progress

Active development, features being implemented

| Metric | Count |
|--------|-------|
| Breaking Changes | 0 |
| New Features | 7 |
| Bug Fixes | 2 |
| Other Changes | 14 |

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
| Header Files | 22 |
| Source Files | 22 |
| Total C++ Files | 44 |
| Total Lines | 2,110 |
| Code Lines | 1,969 |
| Comment Lines | 141 |
| Total Commits | 23 |
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
| Correct Copyright | 44 |
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
            Data/
                CharacterClassInfo.cpp
            Game/
                GameMode/
                    DA_GameMode.cpp
                PlayerController/
                    DA_PlayerController.cpp
                PlayerState/
                    DAPlayerState.cpp
            Input/
                DAInputConfig.cpp
                DASystemsInputComponent.cpp
            Interfaces/
                InventoryInterface.cpp
            Systems/
                AbilitySystem/
                    Abilities/
                        DAGameplayAbility.cpp
                    Attributes/
                        DAAttributeSet.cpp
                    Libraries/
                        DAAbilitySystemLibrary.cpp
                    DAAbilitySystemComponent.cpp
                Inventory/
                    InventoryComponent.cpp
                    ItemTypes.cpp
                    ItemTypesToTables.cpp
            UI/
                WidgetControllers/
                    InventoryWidgetController.cpp
                    WidgetController.cpp
                DASystemsWidget.cpp
        Public/
            Actors/
                EffectActor.h
            Data/
                CharacterClassInfo.h
            Game/
                GameMode/
                    DA_GameMode.h
                PlayerController/
                    DA_PlayerController.h
                PlayerState/
                    DAPlayerState.h
            Input/
                DAInputConfig.h
                DASystemsInputComponent.h
            Interfaces/
                InventoryInterface.h
            Systems/
                AbilitySystem/
                    Abilities/
                        DAGameplayAbility.h
                    Attributes/
                        DAAttributeSet.h
                    Libraries/
                        DAAbilitySystemLibrary.h
                    DAAbilitySystemComponent.h
                Inventory/
                    InventoryComponent.h
                    ItemTypes.h
                    ItemTypesToTables.h
            UI/
                WidgetControllers/
                    InventoryWidgetController.h
                    WidgetController.h
                DASystemsWidget.h
        DA.Build.cs
        DA.cpp
        DA.h
        DACharacter.cpp
        DACharacter.h
        DAGameMode.cpp
        DAGameMode.h
        DAPlayerController.cpp
        DAPlayerController.h
    DA.Target.cs
    DAEditor.Target.cs
```

<!-- DIRECTORY_END -->

<!-- CLASSES_START -->
## C++ Classes

### DA

| Class | Type | Base | Description |
|-------|------|------|-------------|
| `ADACharacter` | Class | `ACharacter` |  |
| `ADAGameMode` | Class | `AGameModeBase` |  |
| `ADAPlayerController` | Class | `APlayerController` |  |
| `ADAPlayerState` | Class | `APlayerState` |  |
| `ADA_GameMode` | Class | `AGameMode` |  |
| `ADA_PlayerController` | Class | `APlayerController` |  |
| `AEffectActor` | Class | `AActor` |  |
| `FCharacterClassDefaultInfo` | Struct | `-` |  |
| `FConsumableProps` | Struct | `-` |  |
| `FDAInputAction` | Struct | `-` |  |
| `FMasterItemDefinition` | Struct | `-` |  |
| `FPackagedInventory` | Struct | `-` |  |
| `UCharacterClassInfo` | Class | `UDataAsset` |  |
| `UDAAbilitySystemComponent` | Class | `UAbilitySystemComponent` |  |
| `UDAAbilitySystemLibrary` | Class | `UBlueprintFunctionLibrary` |  |
| `UDAAttributeSet` | Class | `UAttributeSet` |  |
| `UDAGameplayAbility` | Class | `UGameplayAbility` |  |
| `UDAInputConfig` | Class | `UDataAsset` |  |
| `UDASystemsWidget` | Class | `UUserWidget` |  |
| `UInventoryWidgetController` | Class | `UWidgetController` |  |
| `UItemTypesToTables` | Class | `UDataAsset` |  |
| `UWidgetController` | Class | `UObject` |  |

<!-- CLASSES_END -->

<!-- TAGS_START -->
## Gameplay Tags

### Character
- `Character.Player.Default`

### Input
- `Input.EAbility`
- `Input.QAbility`
- `Input.ShiftAbility`

### Item
- `Item.Consumable.HealthPotion`
- `Item.Consumable.ManaPotion`

<!-- TAGS_END -->

<!-- COMMITS_START -->
## Recent Changes

- [`eb95418`](https://github.com/Raio-Core/DarkAge/commit/eb95418bed29a2200de5db58ed25130007e57ac9) Merge remote-tracking branch 'origin/main' (2026-02-27)
- [`ce3bc04`](https://github.com/Raio-Core/DarkAge/commit/ce3bc0467fe58e11ed1c3661516651c03f577b4a) Add E ability input binding and fix ability system naming (2026-02-27)
- [`8e5a306`](https://github.com/Raio-Core/DarkAge/commit/8e5a3060a190d4b4e0431955d0c50c50d9962084) docs: auto-update README [skip ci] (2026-02-27)
- [`0f76ddd`](https://github.com/Raio-Core/DarkAge/commit/0f76ddd70a54c3df3f11f0c5542215a2a2f1c6f6) Merge remote-tracking branch 'origin/main' (2026-02-26)
- [`977339c`](https://github.com/Raio-Core/DarkAge/commit/977339ccc9af76474d370881eaf6e801898e8ebb) feat: implement inventory system with widget controller (2026-02-26)
- [`8235eb6`](https://github.com/Raio-Core/DarkAge/commit/8235eb6aca88308dca74ea8f3511e649cc152462) feat(inventory): add item usage with GAS integration (2026-02-25)
- [`f122cd9`](https://github.com/Raio-Core/DarkAge/commit/f122cd9a41f93b4ba5d42ab4ef56195abb867caf) refactor(inventory): rename parameter from InItemTag to Item... (2026-02-24)
- [`7ebbace`](https://github.com/Raio-Core/DarkAge/commit/7ebbace8febe50176954dcbc2c2ce3e3934850d7) docs: auto-update README [skip ci] (2026-02-24)
- [`19db8d8`](https://github.com/Raio-Core/DarkAge/commit/19db8d8976fe467a04fdea5cf6fcc118516d144a) Merge remote-tracking branch 'origin/main' (2026-02-24)
- [`b4d46d4`](https://github.com/Raio-Core/DarkAge/commit/b4d46d47b6a69ef00b08131e9113334962b11845) feat(game): add inventory system and mobile controls (2026-02-24)

<!-- COMMITS_END -->

<!-- CONTRIBUTORS_START -->
## Contributors

- **Raio-Core** (17 commits)
- **github-actions[bot]** (4 commits)
- **Raioix** (2 commits)

<!-- CONTRIBUTORS_END -->

---

<p align="center">
  <i>Copyright 2026 RaioCore and Raioix. All Rights Reserved.</i><br><br>
  <i>Last updated: 2026-02-28 01:05:37 UTC</i><br>
  <i>This README is automatically generated from project files and git history.</i><br>
  <i>Version follows semantic versioning based on conventional commits.</i>
</p>
