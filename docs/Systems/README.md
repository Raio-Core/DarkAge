# Systems Documentation

This section provides detailed documentation for the major game systems implemented in DA.

---

## 🔮 Gameplay Ability System

The Gameplay Ability System (GAS) is the core framework for all combat abilities, skills, and gameplay effects.

### Architecture

```mermaid
flowchart TB
    subgraph Player["Player"]
        PC[PlayerController]
        PS[PlayerState]
        Char[Character]
    end
    
    subgraph GAS["Gameplay Ability System"]
        ASC[AbilitySystemComponent]
        GA[GameplayAbility]
        GE[GameplayEffect]
        ATC[AbilityTaskController]
    end
    
    subgraph Data["Data"]
        AS[AttributeSet]
        GT[GameplayTags]
        TC[Tag Container]
    end
    
    PC -->|Implements| ASC
    Char -->|Has| ASC
    ASC -->|Grants| GA
    ASC -->|Applies| GE
    GA -->|Uses| ATC
    ASC -->|Manages| AS
    ASC -->|Uses| TC
    TC -->|References| GT
```

### Core Components

| Component | Description | Class |
|-----------|-------------|-------|
| **Ability System Component** | Central GAS manager | [`UDAAbilitySystemComponent`](../../Source/DA/Public/Systems/AbilitySystem/DAAbilitySystemComponent.h) |
| **Attribute Set** | Character attributes (Health, Stamina, Mana) | [`UDAAttributeSet`](../../Source/DA/Public/Systems/AbilitySystem/Attributes/DAAttributeSet.h) |
| **Gameplay Ability** | Base class for all abilities | [`UDAGameplayAbility`](../../Source/DA/Public/Systems/AbilitySystem/Abilities/DAGameplayAbility.h) |
| **Ability System Library** | Helper functions | [`UDAAbilitySystemLibrary`](../../Source/DA/Public/Systems/AbilitySystem/Libraries/DAAbilitySystemLibrary.h) |

### Attributes

```mermaid
classDiagram
    class UDAAttributeSet {
        +FGameplayAttributeData Health
        +FGameplayAttributeData MaxHealth
        +FGameplayAttributeData Stamina
        +FGameplayAttributeData MaxStamina
        +FGameplayAttributeData Mana
        +FGameplayAttributeData MaxMana
        +PostGameplayEffectExecute()
    }
    
    class UAttributeSet {
        <<Unreal Engine>>
    }
    
    UAttributeSet <|-- UDAAttributeSet
```

### Key Features

- ✅ **Attribute Replication** - Network synchronized attributes
- ✅ **Gameplay Tags** - Flexible tagging system for abilities
- ✅ **Gameplay Effects** - Buffs, debuffs, and modifiers
- ✅ **Ability Tasks** - Async ability execution
- 🔄 **Ability Sets** - Predefined ability loadouts

---

## 📦 Inventory System

A tag-based inventory system with network replication and UI integration.

### Architecture

```mermaid
flowchart TB
    subgraph Actor["Actor"]
        IC[InventoryComponent]
    end
    
    subgraph Data["Item Data"]
        IT[ItemTypes]
        ITT[ItemTypesToTables]
        MD[MasterItemDefinition]
    end
    
    subgraph Network["Network"]
        PI[PackagedInventory]
        Rep[Replication]
    end
    
    subgraph UI["User Interface"]
        IWC[InventoryWidgetController]
        IW[InventoryWidget]
    end
    
    IC -->|Stores| IT
    IT -->|Definitions| ITT
    ITT -->|Lookup| MD
    IC -->|Packages| PI
    PI -->|Replicates| Rep
    IC -->|Delegate| IWC
    IWC -->|Updates| IW
```

### Components

| Component | Description | Class |
|-----------|-------------|-------|
| **Inventory Component** | Main inventory logic | [`UInventoryComponent`](../../Source/DA/Public/Systems/Inventory/InventoryComponent.h) |
| **Item Types** | Item type definitions | [`UItemTypes`](../../Source/DA/Public/Systems/Inventory/ItemTypes.h) |
| **Item Type Tables** | Data table mapping | [`UItemTypesToTables`](../../Source/DA/Public/Systems/Inventory/ItemTypesToTables.h) |

### Key Features

- ✅ **Tag-Based Items** - Items identified by GameplayTags
- ✅ **Network Replication** - Server-authoritative inventory
- ✅ **Packaged Storage** - Efficient network serialization
- ✅ **Item Definitions** - Data-driven item properties
- 🔄 **UI Integration** - Widget controller pattern

### Item Structure

```mermaid
classDiagram
    class UInventoryComponent {
        -TMap~FGameplayTag, int32~ InventoryTagMap
        -FPackagedInventory CachedInventory
        +AddItem()
        +UseItem()
        +GetItemDefinitionByTag()
    }
    
    class FPackagedInventory {
        +TArray~FGameplayTag~ ItemTags
        +TArray~int32~ ItemQuantities
        +NetSerialize()
    }
    
    class FMasterItemDefinition {
        +FGameplayTag ItemTag
        +FText DisplayName
        +UTexture2D Icon
        +EItemType ItemType
    }
    
    UInventoryComponent --> FPackagedInventory
    UInventoryComponent --> FMasterItemDefinition
```

---

## 🎮 Input System

Enhanced Input System for flexible, context-sensitive input handling.

### Architecture

```mermaid
flowchart TB
    subgraph Input["Enhanced Input"]
        IMC[Input Mapping Contexts]
        IA[Input Actions]
        IC[Input Config]
    end
    
    subgraph Handler["Input Handler"]
        PC[PlayerController]
        ISIC[DAInputComponent]
        Tag[GameplayTag]
    end
    
    subgraph Ability["Ability System"]
        ASC[AbilitySystemComponent]
        GA[GameplayAbility]
    end
    
    IMC -->|Triggers| IA
    IA -->|Bound to| ISIC
    ISIC -->|Uses| IC
    ISIC -->|Inputs to| PC
    PC -->|Ability Tags| Tag
    Tag -->|Activates| ASC
    ASC -->|Executes| GA
```

### Components

| Component | Description | Class |
|-----------|-------------|-------|
| **Input Config** | Input action mapping | [`UDAInputConfig`](../../Source/DA/Public/Input/DAInputConfig.h) |
| **Input Component** | Enhanced input handling | [`UDASystemsInputComponent`](../../Source/DA/Public/Input/DASystemsInputComponent.h) |

### Key Features

- ✅ **Context-Based Mapping** - Different contexts for different game states
- ✅ **Gameplay Tag Input** - Direct ability activation via tags
- ✅ **Mobile Support** - Touch control support
- 🔄 **Input Rebinding** - Runtime key remapping

---

## 🎨 UI System

Widget controller pattern for clean UI architecture.

### Architecture

```mermaid
flowchart TB
    subgraph Model["Model"]
        PS[PlayerState]
        IC[InventoryComponent]
        ASC[AbilitySystemComponent]
    end
    
    subgraph Controller["Widget Controllers"]
        WC[WidgetController Base]
        IWC[InventoryWidgetController]
    end
    
    subgraph View["View"]
        SW[SystemsWidget]
        IW[InventoryWidget]
    end
    
    PS -->|Data| WC
    IC -->|Delegate| IWC
    ASC -->|Attributes| WC
    WC -->|Updates| SW
    IWC -->|Updates| IW
```

### Components

| Component | Description | Class |
|-----------|-------------|-------|
| **Base Widget Controller** | Common controller functionality | [`UWidgetController`](../../Source/DA/Public/UI/WidgetControllers/WidgetController.h) |
| **Inventory Widget Controller** | Inventory-specific controller | [`UInventoryWidgetController`](../../Source/DA/Public/UI/WidgetControllers/InventoryWidgetController.h) |
| **Systems Widget** | Base widget class | [`UDASystemsWidget`](../../Source/DA/Public/UI/DASystemsWidget.h) |

### Key Features

- ✅ **Widget Controller Pattern** - Separation of concerns
- ✅ **Data Binding** - Automatic UI updates
- ✅ **Network Replication** - Multiplayer-safe UI
- 🔄 **MVVM Pattern** - Full Model-View-ViewModel

---

## 🔗 Interfaces

Shared interfaces for cross-system communication.

### Available Interfaces

| Interface | Purpose | Class |
|-----------|---------|-------|
| **Inventory Interface** | Standard inventory access | [`IInventoryInterface`](../../Source/DA/Public/Interfaces/InventoryInterface.h) |
| **Ability System Interface** | Standard GAS access | `IAbilitySystemInterface` (UE5 Built-in) |

---

## 🧩 Data Assets

Data-driven configuration assets.

### Character Data

| Asset | Purpose | Class |
|-------|---------|-------|
| **Character Class Info** | Character class definitions | [`UCharacterClassInfo`](../../Source/DA/Public/Data/CharacterClassInfo.h) |

---

## 📋 System Interactions

### Combat Flow

```mermaid
sequenceDiagram
    participant P as Player
    participant IC as InputComponent
    participant PC as PlayerController
    participant ASC as AbilitySystem
    participant Attr as AttributeSet
    
    P->>IC: Press Ability Key
    IC->>PC: Input Tag
    PC->>ASC: Try Activate Ability
    ASC->>ASC: Check Cooldown/Cost
    ASC->>Attr: Consume Stamina/Mana
    ASC->>ASC: Execute Ability
    ASC->>Attr: Apply Effects
```

### Inventory Update Flow

```mermaid
sequenceDiagram
    participant Client as Client
    participant Srv as Server
    participant IC as InventoryComponent
    participant Rep as Replication
    participant UI as UI Widget
    
    Client->>Srv: Request Add Item
    Srv->>IC: AddItem()
    IC->>IC: Update Inventory
    IC->>Rep: Package & Replicate
    Rep->>Client: OnRep_CachedInventory
    IC->>UI: InventoryPackageDelegate
    UI->>UI: Refresh Display
```

---

*For detailed API documentation, see [API Reference](../API/README.md)*
