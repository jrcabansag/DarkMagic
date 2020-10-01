// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleCharacter.h"
#include "TimerManager.h"
#include "EnemyBattleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DARKMAGIC_API AEnemyBattleCharacter : public ABattleCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void StartAttack() override;
	virtual void ShootAttack() override;

private:
	FTimerHandle attackTimerHandle;
	UPROPERTY(EditAnywhere, Category="Enemy AI Properties")
		float SHOOT_ATTACK_TIME = 4.0f;
	UPROPERTY(EditAnywhere, Category = "Enemy AI Properties")
		float CHOOSE_ATTACK_TIME = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Enemy AI Properties")
		float BATTLE_START_WAITING_TIME = 5.0f;
};
