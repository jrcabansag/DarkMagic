// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include "BattleCharacter.h"
#include "DarkMageBattleCharacter.generated.h"

DECLARE_DELEGATE_OneParam(ArrowCallbackDelegate, int);

class ABattleGameMode;
UCLASS()
class DARKMAGIC_API ADarkMageBattleCharacter : public ABattleCharacter
{
	GENERATED_BODY()
private:
	ADarkMageBattleCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ArrowCallbackFunction(int i);
public:
	std::function<void(int)> arrowCallback;
};
