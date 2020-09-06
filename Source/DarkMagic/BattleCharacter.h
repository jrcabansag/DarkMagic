// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "BattleCharacter.generated.h"

UCLASS()
class DARKMAGIC_API ABattleCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	ABattleCharacter();

private:
	UPROPERTY(EditAnywhere)
	int TOTAL_HEALTH = 1000;
	UPROPERTY(EditAnywhere)
	int MESH_HEIGHT = 250;
	UPROPERTY(EditAnywhere)
	int MESH_RADIUS = 40;
	UPROPERTY(EditAnywhere)
	UParticleSystem* HAND_PARTICLES;
	UParticleSystemComponent* leftHandParticleSystem;
	UParticleSystemComponent* rightHandParticleSystem;
	UPROPERTY(EditAnywhere)
	float HAND_PARTICLE_SCALE = 1.0f;
	UPROPERTY(EditAnywhere)
	FVector HAND_PARTICLE_LOCATION;
	int currentHealth;
};
