# 🎮 DA — Dark Age

> An Unreal Engine 5.7 Project | Version 0.4.0 embryo

<p align="center">
  <img src="https://img.shields.io/badge/Unreal%20Engine-5.7-0EBEED?logo=unrealengine&logoColor=white&style=for-the-badge" alt="Unreal Engine">
  <img src="https://img.shields.io/badge/Version-0.4.0-FFD700?style=for-the-badge" alt="Version">
  <img src="https://img.shields.io/badge/Stage-pre--alpha-FF6B6B?style=for-the-badge" alt="Stage">
  <img src="https://img.shields.io/badge/Build-44-4ECDC4?style=for-the-badge" alt="Build">
  <img src="https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white&style=for-the-badge" alt="C++">
</p>

---

## 📚 Table of Contents

- [Overview](#overview)
- [Documentation](#documentation)
- [Version Information](#version-information)
- [Project Statistics](#project-statistics)
- [Project Structure](#project-structure)
- [C++ Classes](#c-classes)
- [Gameplay Tags](#gameplay-tags)
- [Recent Changes](#recent-changes)
- [Contributors](#contributors)
- [Copyright](#copyright)

---

## 🌟 Overview

> *In a world fractured by the Veil, where multiple realities coexist and players shape the story, your choices don't just matter—they define you.*

**Dark Age (DA)** is a multiplayer action RPG set in the **Divided Realm**—a world split between the controlled **Ordered Realm** and the chaotic **Wild Echoes**. Built in Unreal Engine 5.7, Dark Age features a unique blend of deep character progression, player-driven governance, and emergent storytelling.

### 🌍 The World

The world is divided by the **Veil**—a construct designed to separate those who accept control from those who seek freedom:

| Realm | Description |
|-------|-------------|
| **🏛️ Ordered Realm** | Where the Covenants maintain strict control over magic, knowledge, and truth |
| **🌌 Wild Echoes** | Parallel realities where millions of players carve their own destinies |
| **💀 The Void** | The space between Echoes, home to creatures that hunger for life |

### ✨ Core Gameplay

- **No Chosen Hero** — There is no destined savior; your choices define your character
- **Appearance Evolution** — Your character's look changes based on your actions (cruelty hardens you, mercy softens you)
- **Soul Shard Magic** — Master **Additive Magic** (creation) or **Subtractive Magic** (destruction)
- **Player Governance** — Form guilds, build kingdoms, establish laws, levy taxes
- **Persistent Consequences** — The world remembers your deeds; reputation must be earned

### 🎮 Multiplayer Reality

- **Single Mode** (Offline) — Level cap 30, limited to 2 Echoes, no permadeath
- **Multi Mode** (Online) — Full level 100, all 10+ Echoes, permadeath with exclusive benefits
- **Player Kingdoms** — Rule territories, command armies, shape the world
- **Cross-Echo Travel** — Explore parallel realities and project power across dimensional borders

<!-- DESCRIPTION_START -->
### Technical Features

- **Gameplay Ability System** — Full GAS integration with custom ability system component
- **Attribute System** — Replicated attributes for Health, Stamina, and Mana
- **Character Classes** — Flexible character class system with data-driven configuration
- **State Tree** — AI and gameplay logic using Unreal's StateTree plugin
- **Modular Architecture** — Clean separation of systems for maintainability
<!-- DESCRIPTION_END -->

---

## 📖 Documentation

Explore our comprehensive documentation to learn more about the project:

<div align="center">

| 📚 Resource | 📝 Description | 🔗 Link |
|-------------|----------------|---------|
| **Game Design Document** | Complete game design including lore, mechanics, and world-building | [📖 Read GDD](docs/GDD/README.md) |
| **Systems Documentation** | Technical documentation for all game systems | [⚙️ Systems](docs/Systems/README.md) |
| **API Reference** | Auto-generated C++ class documentation | [🔧 API Docs](docs/API/README.md) |
| **Contributing Guide** | Guidelines for contributing to the project | [🤝 Contributing](docs/CONTRIBUTING.md) |
| **Architecture Overview** | High-level technical architecture and design | [🏗️ Architecture](docs/Architecture.md) |

</div>

### 🎮 Game Design Document (GDD)

The GDD contains detailed information about the game world, mechanics, and design philosophy:

| Section | Description |
|---------|-------------|
| [🌍 World](docs/GDD/World.md) | The Divided Realm — Ordered Realm vs Wild Echoes |
| [📖 Story](docs/GDD/Story.md) | Player-driven narrative and emergent storytelling |
| [👥 Characters](docs/GDD/Characters.md) | Key NPCs and character design |
| [✨ Magic](docs/GDD/Magic.md) | Soul Shard magic system (Additive/Subtractive) |
| [🗺️ Locations](docs/GDD/Locations.md) | World locations and environments |
| [🌐 Multiplayer](docs/GDD/Multiplayer.md) | Multiplayer architecture and player governance |
| [💀 Death & Resurrection](docs/GDD/DeathAndResurrection.md) | Soul Anchor system and permadeath mechanics |

### ⚙️ Systems Documentation

Learn about the technical implementation of major game systems:

- [🔮 Gameplay Ability System](docs/Systems/README.md#gameplay-ability-system)
- [📦 Inventory System](docs/Systems/README.md#inventory-system)
- [🎮 Input System](docs/Systems/README.md#input-system)
- [🎨 UI System](docs/Systems/README.md#ui-system)
- [🔗 Interfaces](docs/Systems/README.md#interfaces)
- [🧩 Data Assets](docs/Systems/README.md#data-assets)

---

<!-- VERSION_START -->
## 🏷️ Version Information

| Property | Value |
|----------|-------|
| **Version** | `0.4.0` |
| **Stage** | `pre-alpha` |
| **Build** | `44` |
| **Full Version** | `v0.4.0-pre-alpha+build.44` |

### Development Progress

Active development, features being implemented

| Metric | Count |
|--------|-------|
| Breaking Changes | 0 |
| New Features | 7 |
| Bug Fixes | 2 |
| Other Changes | 22 |

<!-- VERSION_END -->

---

<!-- STATS_START -->
## 📊 Project Statistics

| Metric | Count |
|--------|-------|
| Header Files | 24 |
| Source Files | 24 |
| Total C++ Files | 48 |
| Total Lines | 2,306 |
| Code Lines | 2,155 |
| Comment Lines | 151 |
| Total Commits | 31 |
| Contributors | 3 |

<!-- STATS_END -->

---

<!-- DIRECTORY_START -->
## 🗂️ Project Structure

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
            Character/
                CharacterBasse.h
                DACharacter.h
                EnemyBasse.h
            Data/
                CharacterClassInfo.h
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
    DA.Target.cs
    DAEditor.Target.cs
```

<!-- DIRECTORY_END -->

---

<!-- CLASSES_START -->
## 🧬 C++ Classes

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

---

<!-- TAGS_START -->
## 🏷️ Gameplay Tags

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

---

<!-- COMMITS_START -->
## 📝 Recent Changes

- [`8df741f`](https://github.com/Raio-Core/DarkAge/commit/8df741fe52d2970321ca42043340283393d8f473) refactor(character): extract base character class and add in... (2026-02-27)
- [`184fc70`](https://github.com/Raio-Core/DarkAge/commit/184fc7013050cbee0f8ec6ab081e340fdbc21505) # Changelog (2026-02-27)
- [`3fab266`](https://github.com/Raio-Core/DarkAge/commit/3fab2669b2c244920755d880a722c11a2b59933c) Merge remote-tracking branch 'origin/main' (2026-02-27)
- [`ce49f98`](https://github.com/Raio-Core/DarkAge/commit/ce49f98bb0d0b7495ac38bdc63348593870c0314) docs(gdd): redesign for Dark Age multiplayer focus and emerg... (2026-02-27)
- [`ed1c7f8`](https://github.com/Raio-Core/DarkAge/commit/ed1c7f874986a68a88f8f00cb3f40ca4a840f691) Creating the first draft of the storry and GDD for DarkAge. (2026-02-27)
- [`eaa9c74`](https://github.com/Raio-Core/DarkAge/commit/eaa9c7407f8299e93cfe30507cdbfc215ce6cc7c) Merge remote-tracking branch 'origin/main' (2026-02-27)
- [`4c289ac`](https://github.com/Raio-Core/DarkAge/commit/4c289ac96a909464da9217d16c5e248dd53681fb) docs: add game design document and system overview (2026-02-27)
- [`886369b`](https://github.com/Raio-Core/DarkAge/commit/886369b853bb510bccc24fe5b6d9c59285908e72) docs: auto-update README [skip ci] (2026-02-28)
- [`eb95418`](https://github.com/Raio-Core/DarkAge/commit/eb95418bed29a2200de5db58ed25130007e57ac9) Merge remote-tracking branch 'origin/main' (2026-02-27)
- [`ce3bc04`](https://github.com/Raio-Core/DarkAge/commit/ce3bc0467fe58e11ed1c3661516651c03f577b4a) Add E ability input binding and fix ability system naming (2026-02-27)

<!-- COMMITS_END -->

---

<!-- CONTRIBUTORS_START -->
## 👥 Contributors

- **Raio-Core** (24 commits)
- **github-actions[bot]** (5 commits)
- **Raioix** (2 commits)

<!-- CONTRIBUTORS_END -->

---

<!-- COPYRIGHT_START -->
## 📜 Copyright

Copyright 2026 RaioCore and Raioix. All Rights Reserved.

### Copyright Holders

| Holder | Role |
|--------|------|
| RaioCore | Project Owner |
| Raioix | Project Owner |

### File Copyright Status

| Status | Count |
|--------|-------|
| Correct Copyright | 48 |
| Epic Games (Template) | 0 |
| Placeholder | 0 |
| Missing | 0 |

<!-- COPYRIGHT_END -->

---

<p align="center">
  <a href="docs/GDD/README.md">📖 GDD</a> •
  <a href="docs/Systems/README.md">⚙️ Systems</a> •
  <a href="docs/API/README.md">🔧 API</a> •
  <a href="docs/CONTRIBUTING.md">🤝 Contribute</a>
</p>

<p align="center">
  <i>Copyright 2026 RaioCore and Raioix. All Rights Reserved.</i><br><br>
  <i>Last updated: 2026-02-28 06:13:02 UTC</i><br>
  <i>This README is automatically generated from project files and git history.</i><br>
  <i>Version follows semantic versioning based on conventional commits.</i>
</p>
