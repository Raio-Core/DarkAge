# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

#### Documentation System
- **Auto-updating README** with code statistics and class documentation
- **Python script** (`scripts/generate_docs.py`) for automatic documentation generation from C++ headers
- **GitHub Actions workflow** (`.github/workflows/docs.yml`) for automated doc updates on push
- **Jekyll configuration** (`docs/_config.yml`) for GitHub Pages deployment
- **Custom CSS theme** (`docs/assets/css/style.css`) with dark fantasy styling

#### Game Design Document (GDD)
- **World.md** - The Divided Realm setting with Ordered Realm vs Wild Echoes
- **Story.md** - Player-driven narrative and emergent storytelling
- **Characters.md** - Key NPCs including The Unweaver, Vaelith, Kael, Lyra, Soren, Seraphina
- **Factions.md** - The Covenant, Shatterborn, Echoed factions
- **Magic.md** - Soul Shard manipulation system (Additive/Subtractive magic)
- **Locations.md** - Westbrook, Fractured Citadel, Wild Echoes, Threadsea
- **Multiplayer.md** - Single Mode vs Multi Mode architecture, player governance
- **DeathAndResurrection.md** - Soul Anchor system with permadeath benefits

#### Game Systems Documentation
- **Permadeath Mode Benefits** (exclusive to permadeath):
  - Right to rule as Kings/Queens (only permadeath can be highest rulers)
  - Exclusive crafting of Soul Anchors and Shards of True Life
  - True Sight (Shard Vision) to see hidden Nexus Points
  - Unrestricted Echo travel without cooldowns
  - Legacy Immortality (statues, legendary artifacts, permanent world presence)
  - Deathless Guild (exclusive permadeath-only guild)
  - Economic dominance through control of resurrection economy

#### Mode Differentiation
- **Single Mode** (Offline/Solo):
  - Level cap: 30 (vs 100 in Multi)
  - Loot: Common/Uncommon only
  - No permadeath option
  - No territory control or player governance
  - No guilds
  - Limited to 2 Echoes
  - No legendary crafting
  
- **Multi Mode** (Online):
  - Full level 100 progression
  - All loot rarities including Legendary
  - Permadeath mode with exclusive benefits
  - Territory control and player governance
  - Full player-driven economy
  - Guilds, kingdoms, social structures
  - All 10+ Echoes
  - Legendary crafting (Soul Anchors, Shards of True Life)

#### Anti-Exploit Measures
- Single Mode XP transfers at 50% rate to Multi Mode
- Rare+ items do not transfer between modes
- Gold does not transfer (separate economies)
- Rare+ recipes must be relearned in Multi Mode
- Cannot bypass level cap restrictions

### Changed
- Renamed "shards" to "modes" in multiplayer architecture
- Updated server terminology to reflect Single/Multi Mode system
- Changed governance rules: only permadeath characters can rule as Kings/Queens

### Technical
- Created comprehensive C++ header parser for auto-documentation
- Implemented auto-update markers in README for dynamic content
- Added Mermaid diagram support for architecture visualization
- Set up dark fantasy CSS theme with medieval typography

---

## Template

### Added
- New features

### Changed
- Changes in existing functionality

### Deprecated
- Soon-to-be removed features

### Removed
- Now removed features

### Fixed
- Bug fixes

### Security
- Security improvements
