# The Memory System - Your Past Shapes Your Present

> *"Every choice echoes through time. The Divided Realm doesn't just remember what you did—it remembers who you were. And who you were determines who you can become."*

The Memory System is Dark Age's groundbreaking approach to character progression through choice. Unlike traditional RPGs where your past choices are merely cosmetic or story-specific, in Dark Age, every significant decision creates a permanent "Memory" that actively shapes your character's capabilities, unlocks unique abilities, affects how NPCs perceive you, and even changes the physical world around you.

---

## Core Philosophy

The Memory System is built on four transformative principles:

1. **Choices Have Weight** - Every decision creates lasting mechanical consequences
2. **The Past Is Never Gone** - Memories persist through death and character creation
3. **Identity Is Cumulative** - Multiple characters create a rich history that informs future choices
4. **The World Remembers** - NPCs and locations react to your accumulated history

---

## Understanding Memories

### What Are Memories?

Memories are permanent records of significant choices made during gameplay. They are not simple achievements—they are active gameplay elements that:

- Modify your abilities
- Unlock unique interactions
- Affect NPC dialogue and reactions
- Influence world state
- Carry over between characters

### Memory Categories

Memories fall into several categories:

| Category | Description | Example Choices |
|----------|-------------|-----------------|
| **Karma Memories** | Moral choices made | Spared vs. killed, helped vs. exploited |
| **Combat Memories** | How you fight | Used ranged/melee, solo/party |
| **Social Memories** | How you interact | Befriended/enemies made, leader/follower |
| **Exploration Memories** | What you've discovered | Found secrets, explored locations |
| **Crafting Memories** | How you create | Specialized disciplines, mass craft vs. quality |
| **Legacy Memories** | Deaths and failures | Died to bosses, failed quests, lost battles |

---

## Memory Acquisition

### How Memories Form

Memories are created through significant choices:

**Automatic Memories**
- Quest completion (major story decisions)
- Combat victories/losses (specific enemy types)
- NPC interactions (helping vs. harming)
- World state changes (territory captures)

**Choice-Based Memories**
- Dialogue options that define character
- Skill selection that shows preferences
- Item choices that reflect values
- Alliance decisions that shape identity

**Hidden Memories**
- Patterns of behavior over time
- Preferred playstyles
- Survival patterns
- Achievement combinations

### Memory Strength

Memories have varying "strength" based on significance:

| Strength Level | Trigger Condition | Effect Multiplier |
|---------------|-------------------|-------------------|
| **Faint** | Single minor choice | 1.0x |
| **Clear** | Multiple similar choices | 1.5x |
| **Vivid** | Major story decision | 2.0x |
| **Pivotal** | World-changing choice | 3.0x |
| **Legendary** | Server-first or unique | 5.0x |

---

## Memory Mechanics

### Memory Slots

Each character has Memory Slots that can hold acquired memories:

- **Base Slots**: 10
- **Level Bonus**: +1 per 10 levels (max +10)
- **Item Bonus**: Equipment can add slots
- **Special Bonus**: Certain choices unlock permanent extra slots

### Memory Activation

Memories can be "activated" to gain their effects:

```cpp
// Memory types and activation
enum class EMemoryActivationType
{
    Passive,        // Always active
    Situational,    // Active in specific conditions
    Triggered,      // Activates on specific events
    Charged,        // Limited uses per rest/real-world day
};
```

### Memory Synergy

Certain memories combine to create powerful effects:

**Karma Synergy**
- 5 "Killed [Enemy Type]" memories: +15% damage against that type
- 10 "Spared [Enemy Type]" memories: They won't attack you first

**Combat Synergy**
- 20 "Perfect Dodge" memories: Unlock "Prey Reflexes" passive
- 50 "Counter Attack" memories: Counters have 50% lifesteal

---

## The Karma System - Moral Memories

### Understanding Karma

Karma is the aggregate of your moral memories, representing your character's ethical alignment. It's not simple good vs. evil—it tracks multiple moral dimensions:

### Karma Axes

| Axis | Low End | High End | Meaning |
|------|---------|----------|---------|
| **Compassion** | Ruthless | Merciful | Help others vs. exploit them |
| **Honor** | Dishonorable | Honorable | Rules matter vs. results matter |
| **Order** | Chaotic | Lawful | Freedom vs. structure |
| **Sacrifice** | Selfish | Selfless | Personal gain vs. group benefit |

### Karma-Based Unlocks

Your Karma determines available abilities:

**Merciful Path (High Compassion)**
- Pacifist abilities
- Enemy conversion (turn enemies to your side)
- NPC favor bonuses
- Reduced aggression from creatures

**Ruthless Path (Low Compassion)**
- Fear-based abilities
- Intimidation bonuses
- Loot bonuses from enemies
- Enemy drops increased

**Honorable Path (High Honor)**
- Duelist abilities
- Challenge-based combat
- Reputation bonuses
- Equipment durability

**Chaotic Path (Low Honor)**
- Trickster abilities
- Stealth bonuses
- Unexpected attack bonuses
- Trap creation

---

## Memory-Based Abilities

### The Memory Skill Tree

Instead of traditional skill trees, Dark Age uses Memory-Based abilities that unlock based on accumulated memories:

### Combat Memory Abilities

| Required Memory | Unlocked Ability | Effect |
|----------------|------------------|--------|
| 50 kills with Sword | **Blade Memory** | +10% sword damage |
| 25 perfect parries | **Parry Mastery** | Counters deal 50% more damage |
| 100 enemies dodged | **Evasive Thoughts** | +15% dodge chance |
| 10 boss kills solo | **Giant Slayer** | +25% boss damage |
| Died 5 times to fire | **Fire Survivor** | +50% fire resistance |

### Story Memory Abilities

| Required Memory | Unlocked Ability | Effect |
|----------------|------------------|--------|
| Saved [NPC Name] | **Protector's Bond** | That NPC helps in combat |
| Betrayed [Faction] | **Traitor's Edge** | +30% against that faction |
| Solved [Puzzle Type] | **Puzzle Solver** | Future puzzles solved faster |
| Discovered [Location] | **Pathfinder** | Shown hidden paths |

### Karma Ability Examples

**The Mercy Strike** (Requires: 10 memories of sparing enemies)
- Execute a weakened enemy to convert them to an ally instead
- Ally has 50% of your stats and fights for 2 minutes

**The Final Word** (Requires: 50 honorable decisions)
- In duels, your first attack cannot be blocked
- Psychological warfare: enemies hesitate

**The Blood Debt** (Requires: 10 revenge kills)
- Deal 200% damage to enemies who previously killed you
- Visual: Red aura when fighting such enemies

---

## Memory Echoes - Parallel Possibilities

### What Are Memory Echoes?

When you make a significant choice, an "Echo" is created in the multiverse—a parallel version of you who made the opposite choice. These Echoes occasionally manifest in the world, presenting opportunities or challenges.

### Echo Encounters

**The Opposing Self**
- An Echo from a reality where you made the opposite choice appears
- Fighting them grants the "Memory" of their path
- Victory grants ability related to their choices

**The What-If**
- A version of yourself from a timeline where you made different decisions
- Can trade memories (give them a memory, take theirs)
- Creates new playstyle possibilities

**The Lost Timeline**
- A world where your choices led to disaster
- Help restore that timeline for major rewards
- If you fail, gain "Doomseer" ability (see your failures)

### Echo Memory Transfer

Through Echo encounters, you can:

- Temporarily borrow abilities from alternate selves
- Permanently acquire a second "path" of memories
- Create "Echo Pets" from defeated parallel selves

---

## Memory and the Living World

### NPC Memory of You

NPCs remember your past actions:

**Individual NPC Memory**
- Merchants remember if you helped or robbed them
- Pricing adjusts based on reputation (+/- 50%)
- They share information (or withhold it) based on trust

**Faction Memory**
- Factions track your entire history with them
- Actions in one territory affect all territories
- Summary: "The Defiler" vs "The Champion"

**World Memory**
- Locations remember significant events
- A forest you saved will be beautiful
- A village you abandoned will be ruined

### The Memory Landscape

Your personal history creates a "Memory Landscape"—a unique version of the world:

- Locations you've visited appear differently to you
- Your memories affect what you find (lore, secrets)
- Enemies you've killed often stay dead in your timeline

---

## Cross-Character Memory

### Account Memory Bank

All characters on an account share a "Memory Bank":

**Shared Karma**
- Some Karma points transfer between characters
- Family members start with ancestor's Karma

**Memory Inheritance**
- Upon character death, select one memory to "inherit"
- New character starts with that memory active

**Legacy Memories**
- Unique memories from legendary characters become family heirlooms
- Can be equipped as "Legacy Items" granting memory bonuses

### The Ancestral Lineage

When creating a new character, you can choose an "Ancestor"—a previous character:

| Ancestor Type | Bonus | Requirement |
|--------------|-------|-------------|
| **Parent** | +1 Memory Slot | Character reached level 20 |
| **Grandparent** | +5% XP | Character reached level 50 |
| **Legacy Hero** | +10% all stats | Character entered Hall of Legends |

---

## Memory Corruption - The Dark Side

### What Is Memory Corruption?

Making choices against your established character can cause "Memory Corruption":

**Corruption Effects**
- Abilities become unstable (random failure)
- Karma becomes confused (effects cancel out)
- NPC trust decreases

### Corruption Sources

- Doing the opposite of your established memories
- Using abilities you've "forgotten"
- Betraying your past allies
- Killing your former friends

### Corruption Removal

**Purification Quests**
- Complete tasks matching your original path
- Removes corruption over time

**The Memory Purge**
- Use special item to clear all memories
- Dangerous: loses all memory-based abilities
- Sometimes necessary for new playstyles

---

## Technical Implementation

### Memory Data Structure

```cpp
// Individual Memory
struct FCharacterMemory
{
    FString MemoryID;
    EMemoryCategory Category;
    EMemoryStrength Strength;
    float EffectValue;
    EMemoryActivationType ActivationType;
    
    // Conditions
    FGameplayTagContainer RequiredTags;
    TArray<FName> RequiredMemories;  // For synergy
    
    // Persistence
    FDateTime AcquiredDate;
    bool bIsActive;
    int32 ChargesRemaining;  // For charged memories
};

// Memory Bank (Account-Level)
struct FMemoryBank
{
    TArray<FCharacterMemory> EarnedMemories;
    TArray<FCharacterMemory> InheritedMemories;
    TArray<FKarmaAxis> KarmaLevels;
    int32 TotalKarmaPoints;
    
    // Cross-character tracking
    TMap<FString, FCharacterMemory> AncestorMemories;
};
```

### Memory Processing

```cpp
void UMemorySystem::ProcessChoice(FChoiceMade Choice)
{
    // Create new memory based on choice
    FCharacterMemory NewMemory = CreateMemoryFromChoice(Choice);
    
    // Check for synergies with existing memories
    TArray<FCharacterMemory> Synergies = CheckSynergies(NewMemory);
    for (auto& Synergy : Synergies)
    {
        Synergy.ActivateEffect();
    }
    
    // Update Karma
    UpdateKarma(Choice);
    
    // Check for corruption
    if (CheckForCorruption(NewMemory))
    {
        ApplyCorruption();
    }
    
    // Save to database
    SaveToMemoryBank(NewMemory);
    
    // Notify UI
    OnMemoryCreated.Broadcast(NewMemory);
}
```

### Memory Ability Activation

```cpp
float UMemoryAbilityComponent::CalculateMemoryBonus(
    EMemoryCategory Category,
    FGameplayTagContainer Context
)
{
    float TotalBonus = 0.0f;
    
    for (const FCharacterMemory& Memory : ActiveMemories)
    {
        if (Memory.Category == Category && 
            Memory.IsApplicable(Context))
        {
            TotalBonus += Memory.EffectValue * Memory.StrengthMultiplier;
        }
    }
    
    return TotalBonus;
}
```

---

## Addictive Design Elements

### The "What If" Curiosity

> *"I wonder what would have happened if I chose differently?"*

- Echo encounters satisfy curiosity
- New characters encourage experimentation
- No choice feels permanent

### The "Complete My Story" Motivation

> *"I need just one more memory to unlock that ability..."*

- Visible progress toward memory unlocks
- Achievements track memory acquisition
- Endless content: thousands of memory combinations

### The "My Character Is Unique" Pride

> *"No one else has exactly my memory combination!"*

- Creates true character uniqueness
- Players share memory builds
- Community strategies emerge

---

## Memory Collections

### Special Memory Sets

Certain memories combine into powerful sets:

**The Redeemer Set** (10 memories of giving enemies second chances)
- Full set: Mercy Strike becomes "Redemption" - Convert permanently
- +50% experience when showing mercy
- Enemies automatically flee when low health

**The Destroyer Set** (50 memories of destroying specific type)
- Full set: "Annihilation" - That type can never spawn in your world
- +100% damage against that type
- They drop double loot

**The Legend Set** (100 memories of world-first achievements)
- Full set: Your name appears in Chronicle forever
- Unique aura visible to all players
- All abilities gain +10%

---

## Memory Events

### Memory Week

Weekly event celebrating memories:

- Double memory acquisition
- "Memory Lane" special quests: relive past choices
- Trade memories with other players

### The Memory Palace

Monthly event: Enter a special dungeon based on your memories:
- Each room is a past choice
- Navigate to create new memories
- Endless mode: how far can you go?

---

## Related Systems

- [Momentum System](MomentumSystem.md) - Memory and Flow State synergy
- [Legacy System](LegacySystem.md) - Cross-character memory inheritance
- [Echo System](EchoSystem.md) - Parallel reality memory echoes
- [Karma System](KarmaSystem.md) - Moral memory tracking
- [Quest System](QuestsAndMissions.md) - Choice-based quest memories

---

*"We are not defined by what we have, but by what we remember. And in the Divided Realm, what we remember becomes real." — The Keeper of Memories*
