// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include "BattleCharacter.h"
#include "PlayerBattleCharacter.generated.h"

DECLARE_DELEGATE_OneParam(ArrowCallbackDelegate, int);

class ABattleGameMode;
UCLASS()
class DARKMAGIC_API APlayerBattleCharacter : public ABattleCharacter
{
	GENERATED_BODY()

public:
	void Init(ABattleCharacter* initOpponent, std::function<void(int, int)> initUpdateHealthCallback, std::function<void(int)> initArrowCallback, std::function<void(int)> initHitCallback);
	virtual void StartAttack() override;
	std::function<void(int)> arrowCallback;

private:
	APlayerBattleCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ArrowCallbackFunction(int i);
};
