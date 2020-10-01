// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBattleCharacter.h"

APlayerBattleCharacter::APlayerBattleCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerBattleCharacter::Init(ABattleCharacter* initOpponent, std::function<void(int, int)> initUpdateHealthCallback, std::function<void(int)> initArrowCallback)
{
	Super::Init(initOpponent, initUpdateHealthCallback);
	arrowCallback = initArrowCallback;
}

void APlayerBattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("DARK MAGE BATTLE CHARACTER SET UP PLAYER INPUT"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Up", IE_Pressed, this, &APlayerBattleCharacter::ArrowCallbackFunction, 0);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Down", IE_Pressed, this, &APlayerBattleCharacter::ArrowCallbackFunction, 1);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Left", IE_Pressed, this, &APlayerBattleCharacter::ArrowCallbackFunction, 2);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Right", IE_Pressed, this, &APlayerBattleCharacter::ArrowCallbackFunction, 3);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Reset", IE_Pressed, this, &APlayerBattleCharacter::ArrowCallbackFunction, -1);
}

void APlayerBattleCharacter::ArrowCallbackFunction(int i)
{
	if (arrowCallback) {
		arrowCallback(i);
	}
}

void APlayerBattleCharacter::StartAttack()
{
	Super::StartAttack();
}