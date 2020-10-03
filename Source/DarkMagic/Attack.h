// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <functional>
#include "Animation/AnimMontage.h"
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
	UAnimMontage* GetAnimMontage();
	void Die();

private:
	int damage;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	void SetSpeed();
	UPROPERTY(VisibleAnywhere, Category="Projectile Properties")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Projectile Properties")
	UProjectileMovementComponent* ProjectileMovementComponent;
	ABattleCharacter* spawnCharacter;
	ABattleCharacter* targetCharacter;
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	FVector SPAWN_OFFSET;
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	int MIN_DAMAGE = 100;
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	int MAX_DAMAGE = 100;
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	int PROJECTILE_SPEED = 1500;
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	UAnimMontage* animMontage;
};
