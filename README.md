# DA

> An Unreal Engine 5.7 Project | Version 0.4.0 embryo

<!-- BADGES_START -->
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-0EBEED?logo=unrealengine&logoColor=white)](https://www.unrealengine.com/)
[![Version](https://img.shields.io/badge/Version-0.4.0-lightgrey)]()
[![Stage](https://img.shields.io/badge/Stage-pre--alpha-lightgrey)]()
[![Build](https://img.shields.io/badge/Build-28-blue)]()
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
<!-- BADGES_END -->

<!-- VERSION_START -->
## Version Information

| Property | Value |
|----------|-------|
| **Version** | `0.4.0` |
| **Stage** | `pre-alpha` |
| **Build** | `28` |
| **Full Version** | `v0.4.0-pre-alpha+build.28` |

### Development Progress

Active development, features being implemented

| Metric | Count |
|--------|-------|
| Breaking Changes | 0 |
| New Features | 5 |
| Bug Fixes | 2 |
| Other Changes | 8 |

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
| Header Files | 13 |
| Source Files | 13 |
| Total C++ Files | 26 |
| Total Lines | 1,354 |
| Code Lines | 1,264 |
| Comment Lines | 90 |
| Total Commits | 15 |
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
| Correct Copyright | 26 |
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
            Systems/
                AbilitySystem/
                    Attributes/
                        DAAttributeSet.cpp
                    Libraries/
                        DAAbilitySystemLibrary.cpp
                    DAAbilitySystemComponent.cpp
                Inventory/
                    InventoryComponent.cpp
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
            Systems/
                AbilitySystem/
                    Attributes/
                        DAAttributeSet.h
                    Libraries/
                        DAAbilitySystemLibrary.h
                    DAAbilitySystemComponent.h
                Inventory/
                    InventoryComponent.h
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
| `FPackagedInventory` | Struct | `-` |  |
| `UCharacterClassInfo` | Class | `UDataAsset` |  |
| `UDAAbilitySystemComponent` | Class | `UAbilitySystemComponent` |  |
| `UDAAbilitySystemLibrary` | Class | `UBlueprintFunctionLibrary` |  |
| `UDAAttributeSet` | Class | `UAttributeSet` |  |

<!-- CLASSES_END -->

<!-- TAGS_START -->
## Gameplay Tags

### Character
- `Character.Player.Default`

### Item
- `Item.Consumable.HealthPotion`
- `Item.Consumable.ManaPortion`

<!-- TAGS_END -->

<!-- COMMITS_START -->
## Recent Changes

- [`19db8d8`](https://github.com/Raio-Core/DarkAge/commit/19db8d8976fe467a04fdea5cf6fcc118516d144a) Merge remote-tracking branch 'origin/main' (2026-02-24)
- [`b4d46d4`](https://github.com/Raio-Core/DarkAge/commit/b4d46d47b6a69ef00b08131e9113334962b11845) feat(game): add inventory system and mobile controls (2026-02-24)
- [`41366c3`](https://github.com/Raio-Core/DarkAge/commit/41366c3311b3bebc382b7c728d4e90f9b50888f5) docs: auto-update README [skip ci] (2026-02-22)
- [`411a70e`](https://github.com/Raio-Core/DarkAge/commit/411a70e34b2637512b01c63ac2fdf3e7bd86e75e) fix(readme): escape hyphen in stage badge for shields.io (2026-02-17)
- [`6c79532`](https://github.com/Raio-Core/DarkAge/commit/6c7953219238923735832c7b6ed85704bcf1885c) fix(readme): escape hyphens in stage badge for shields.io (2026-02-17)
- [`a53341e`](https://github.com/Raio-Core/DarkAge/commit/a53341e60e78d246940e9518ff36798b9529221e) Merge remote-tracking branch 'origin/main' (2026-02-17)
- [`f931dd6`](https://github.com/Raio-Core/DarkAge/commit/f931dd62ae7b2bbfef1448bd23b9bb8d92afac23) docs(readme): escape hyphen in stage badge URL for shields.i... (2026-02-17)
- [`3de0221`](https://github.com/Raio-Core/DarkAge/commit/3de0221339e63e144d2391fb49fd9658e190edf9) docs: auto-update README [skip ci] (2026-02-18)
- [`ec87485`](https://github.com/Raio-Core/DarkAge/commit/ec87485c0a0a795417f53d125b0f93b73ae2a20a) chore(branding): update copyright headers and add GAS interf... (2026-02-17)
- [`8981e83`](https://github.com/Raio-Core/DarkAge/commit/8981e83b90d035a5356618af64fe9442882e9d2c) feat(ability-system): add stamina and mana attributes with c... (2026-02-17)

<!-- COMMITS_END -->

<!-- CONTRIBUTORS_START -->
## Contributors

- **Raio-Core** (11 commits)
- **Raioix** (2 commits)
- **github-actions[bot]** (2 commits)

<!-- CONTRIBUTORS_END -->

---

<p align="center">
  <i>Copyright 2026 RaioCore and Raioix. All Rights Reserved.</i><br><br>
  <i>Last updated: 2026-02-24 17:50:31 UTC</i><br>
  <i>This README is automatically generated from project files and git history.</i><br>
  <i>Version follows semantic versioning based on conventional commits.</i>
</p>
