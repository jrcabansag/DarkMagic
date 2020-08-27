// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattleGameMode.h"
#include "DarkMagePawn.generated.h"

UCLASS()
class DARKMAGIC_API ADarkMagePawn : public APawn
{
	GENERATED_BODY()
private:
	const int TOTAL_HEALTH = 500;
	int currentHealth;
	ABattleGameMode* battleGameMode;
	void Up();
	void Down();
	void Left();
	void Right();
	void Reset();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
public:
	ADarkMagePawn();
};
