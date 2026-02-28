# ADAPlayerController

*Basic PlayerController class for a third person game Manages input mappings*

**File:** `Source\DA\DAPlayerController.h`

## Inheritance

```
APlayerController -> ADAPlayerController
```

## Specifiers

`abstract`

## Properties

| Name | Type | Specifiers | Category |
|------|------|------------|----------|
| `unknown` | `TArray<UInputMappingContext*>` | EditAnywhere | `Input|Input Mappings` |<br>_Input Mapping Contexts_
| `unknown` | `TArray<UInputMappingContext*>` | EditAnywhere | `Input|Input Mappings` |<br>_Input Mapping Contexts_
| `unknown` | `TSubclassOf<UUserWidget>` | EditAnywhere | `Input|Touch Controls` |<br>_Mobile controls widget to spawn_
| `unknown` | `TObjectPtr<UUserWidget>` | - | - |<br>_Pointer to the mobile controls widget_
| `=` | `bool bForceTouchControls` | EditAnywhere | Config | `Input|Touch Controls` |<br>_If true, the player will use UMG touch controls even if not playing on mobile platforms_
