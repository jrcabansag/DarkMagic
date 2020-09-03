// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/SkeletalMesh.h"
#include "BattleCharacter.generated.h"

UCLASS()
class DARKMAGIC_API ABattleCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	ABattleCharacter();

private:
	UPROPERTY(EditAnywhere)
	int TOTAL_HEALTH;
	int currentHealth;
};
