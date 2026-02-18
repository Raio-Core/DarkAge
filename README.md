# DA

> An Unreal Engine 5.7 Project | Version 0.3.0 embryo

<!-- BADGES_START -->
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-0EBEED?logo=unrealengine&logoColor=white)](https://www.unrealengine.com/)
[![Version](https://img.shields.io/badge/Version-0.3.0-lightgrey)]()
[![Stage](https://img.shields.io/badge/Stage-pre-alpha-lightgrey)]()
[![Build](https://img.shields.io/badge/Build-13-blue)]()
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
<!-- BADGES_END -->

<!-- VERSION_START -->
## Version Information

| Property | Value |
|----------|-------|
| **Version** | `0.3.0` |
| **Stage** | `pre-alpha` |
| **Build** | `13` |
| **Full Version** | `v0.3.0-pre-alpha+build.13` |

### Development Progress

Active development, features being implemented

| Metric | Count |
|--------|-------|
| Breaking Changes | 0 |
| New Features | 4 |
| Bug Fixes | 0 |
| Other Changes | 2 |

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
| Header Files | 11 |
| Source Files | 11 |
| Total C++ Files | 22 |
| Total Lines | 988 |
| Code Lines | 916 |
| Comment Lines | 72 |
| Total Commits | 6 |
| Contributors | 2 |

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
| Correct Copyright | 22 |
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
                PlayerState/
                    DAPlayerState.cpp
            Systems/
                AbilitySystem/
                    Attributes/
                        DAAttributeSet.cpp
                    Libraries/
                        DAAbilitySystemLibrary.cpp
                    DAAbilitySystemComponent.cpp
        Public/
            Actors/
                EffectActor.h
            Data/
                CharacterClassInfo.h
            Game/
                GameMode/
                    DA_GameMode.h
                PlayerState/
                    DAPlayerState.h
            Systems/
                AbilitySystem/
                    Attributes/
                        DAAttributeSet.h
                    Libraries/
                        DAAbilitySystemLibrary.h
                    DAAbilitySystemComponent.h
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
| `AEffectActor` | Class | `AActor` |  |
| `FCharacterClassDefaultInfo` | Struct | `-` |  |
| `UCharacterClassInfo` | Class | `UDataAsset` |  |
| `UDAAbilitySystemComponent` | Class | `UAbilitySystemComponent` |  |
| `UDAAbilitySystemLibrary` | Class | `UBlueprintFunctionLibrary` |  |
| `UDAAttributeSet` | Class | `UAttributeSet` |  |

<!-- CLASSES_END -->

<!-- TAGS_START -->
## Gameplay Tags

### Character
- `Character.Player.Default`

<!-- TAGS_END -->

<!-- COMMITS_START -->
## Recent Changes

- [`8981e83`](https://github.com/Raio-Core/DarkAge.git/commit/8981e83b90d035a5356618af64fe9442882e9d2c) feat(ability-system): add stamina and mana attributes with c... (2026-02-17)
- [`f97c653`](https://github.com/Raio-Core/DarkAge.git/commit/f97c653fab4a2e64c69b38c0e6aa86889d3a4eaa) feat(character): update third person character blueprint and... (2026-02-15)
- [`cb04ca2`](https://github.com/Raio-Core/DarkAge.git/commit/cb04ca2fef517998be55c742e2985a014c4e10cf) refactor: update net frequency setter and extend ability sys... (2026-02-15)
- [`74d4107`](https://github.com/Raio-Core/DarkAge.git/commit/74d41071369889d62031b9b16d722bcbfb1b5149) feat: enhance character class and ability system integration (2026-02-15)
- [`9cd691e`](https://github.com/Raio-Core/DarkAge.git/commit/9cd691ed650e2bce596fc6a1989de17d9c6023c9) feat: integrate ability system and attributes with player st... (2026-02-13)
- [`7997ca2`](https://github.com/Raio-Core/DarkAge.git/commit/7997ca2c6666b48ccdb1edb5d9a3e42185951a2c) Initial commit - Unreal Engine project setup (2026-02-13)

<!-- COMMITS_END -->

<!-- CONTRIBUTORS_START -->
## Contributors

- **Raio-Core** (4 commits)
- **Raioix** (2 commits)

<!-- CONTRIBUTORS_END -->

---

<p align="center">
  <i>Copyright 2026 RaioCore and Raioix. All Rights Reserved.</i><br><br>
  <i>Last updated: 2026-02-18 05:01:52 UTC</i><br>
  <i>This README is automatically generated from project files and git history.</i><br>
  <i>Version follows semantic versioning based on conventional commits.</i>
</p>
