# AEffectActor

**File:** `Source\DA\Public\Actors\EffectActor.h`

## Inheritance

```
AActor -> AEffectActor
```

## Properties

| Name | Type | Specifiers | Category |
|------|------|------------|----------|
| `TObjectPtr<UStaticMeshComponent>` | `)` | VisibleAnywhere | meta | - |
| `TObjectPtr<UBoxComponent>` | `)` | VisibleAnywhere | meta | - |
| `unknown` | `TSubclassOf<UGameplayEffect>` | EditAnywhere | `Custom Values|Effects` |

## Functions

| Name | Return Type | Parameters | Specifiers |
|------|-------------|------------|------------|
| `OnBoxBeginOverlap` | `void` | `UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult` | - |
