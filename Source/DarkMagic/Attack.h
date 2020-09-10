// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <functional>
#include "Attack.generated.h"

class ABattleCharacter;
UCLASS()
class DARKMAGIC_API AAttack : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAttack();
	void Init(ABattleCharacter* initSpawnCharacter, ABattleCharacter* initTargetCharacter);
	ABattleCharacter* GetTargetCharacter();
	int GetDamage();
	void Die();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	void SetSpeed();
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	ABattleCharacter* spawnCharacter;
	ABattleCharacter* targetCharacter;
	UPROPERTY(EditAnywhere)
	FVector SPAWN_OFFSET;
	UPROPERTY(EditAnywhere)
	int DAMAGE = 100;
	UPROPERTY(EditAnywhere)
	int PROJECTILE_SPEED = 1500;
};
