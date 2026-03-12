# AProjectileBase

**File:** `Source\DA\Public\Projectiles\ProjectileBase.h`

## Inheritance

```
AActor -> AProjectileBase
```

## Properties

| Name | Type | Specifiers | Category |
|------|------|------------|----------|
| `TObjectPtr<UStaticMeshComponent>` | `)` | VisibleAnywhere | meta | - |
| `TObjectPtr<USphereComponent>` | `)` | VisibleAnywhere | meta | - |
| `unknown` | `TObjectPtr<UProjectileMovementComponent>` | - | - |
| `unknown` | `FGameplayTag` | ReplicatedUsing | - |
| `unknown` | `TObjectPtr<UObject>` | ReplicatedUsing | - |
| `unknown` | `FDamageEffectInfo` | BlueprintReadWrite | - |

## Functions

| Name | Return Type | Parameters | Specifiers |
|------|-------------|------------|------------|
| `OnRep_ProjectileTag` | `void` | - | - |
| `OnRep_ProjectileMesh` | `void` | - | - |
| `OnSphereBeginOverlap` | `virtual void` | `UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult` | - |
