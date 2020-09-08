// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BattleCharacter.h"
#include <functional>
#include "Projectile.generated.h"

UCLASS()
class DARKMAGIC_API AProjectile : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void Init(ABattleCharacter* initSpawnCharacter, ABattleCharacter* initTargetCharacter, std::function<void(int)> initDamageCallback);
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UFUNCTION()
	void OnMeshBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
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
	std::function<void(int)> damageCallback;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
