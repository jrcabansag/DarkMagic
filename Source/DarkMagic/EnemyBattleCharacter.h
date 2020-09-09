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

private:
	FTimerHandle attackTimerHandle;
	UPROPERTY()
		float ATTACK_TIMER_DURATION = 5.0f;
};
