// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/SkeletalMesh.h"
#include <functional>
#include "Attack.h"
#include "Engine/World.h"
#include "BattleCharacter.generated.h"

UCLASS()
class DARKMAGIC_API ABattleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	void Init(ABattleCharacter* initOpponent, std::function<void(int, int)> initUpdateHealthCallback);
	virtual void NotifyToSpawnAttack();
	virtual void NotifyToPauseAttack();
	virtual void ShootAttack();
	virtual void StopAttack();

protected:
	ABattleCharacter();
	virtual void StartAttack();
	virtual void SpawnAttack();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	UWorld* world;

private:
	UAnimInstance* animInstance;
	UAnimMontage* animMontage;
	UPROPERTY(EditAnywhere)
	int TOTAL_HEALTH = 1000;
	UPROPERTY(EditAnywhere)
	int MESH_HEIGHT = 250;
	UPROPERTY(EditAnywhere)
	int MESH_RADIUS = 40;
	UPROPERTY(EditAnywhere)
	UParticleSystem* HAND_PARTICLES;
	UParticleSystemComponent* LeftHandParticleSystemComponent;
	UParticleSystemComponent* RightHandParticleSystemComponent;
	UPROPERTY(EditAnywhere)
	float HAND_PARTICLE_SCALE = 1.0f;
	UPROPERTY(EditAnywhere)
	FVector HAND_PARTICLE_LOCATION;
	void InitHandParticleSystemComponent(UParticleSystemComponent*& handParticleSystemComponent, FName componentName, FName componentToAttachToName);
	void SetUpHandParticleSystemComponent(UParticleSystemComponent* handParticleSystemComponent);
	USkeletalMeshComponent* MeshComponent;
	void AdjustMeshToSize();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAttack> ATTACK;
	ABattleCharacter* opponent;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	void HitByAttack(AAttack* attack);
	void UpdateHealth(int healthChange);
	std::function<void(int, int)> updateHealthCallback;
	int currentHealth;
	UPROPERTY(EditAnywhere)
	UAnimMontage* STANCE_ANIM_MONTAGE;
};
