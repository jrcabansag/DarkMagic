// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <functional>
#include "DarkMagePawn.generated.h"

DECLARE_DELEGATE_OneParam(ArrowCallbackDelegate, int);

class ABattleGameMode;
UCLASS()
class DARKMAGIC_API ADarkMagePawn : public APawn
{
	GENERATED_BODY()
private:
	ADarkMagePawn();
	int TOTAL_HEALTH = 500;
	int currentHealth;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	void ArrowCallbackFunction(int i);
public:
	std::function<void(int)> arrowCallback;
};
