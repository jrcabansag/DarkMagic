// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMageBattleCharacter.h"

ADarkMageBattleCharacter::ADarkMageBattleCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ADarkMageBattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("DARK MAGE PAWN SET UP PLAYER INPUT"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Up", IE_Pressed, this, &ADarkMageBattleCharacter::ArrowCallbackFunction, 0);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Down", IE_Pressed, this, &ADarkMageBattleCharacter::ArrowCallbackFunction, 1);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Left", IE_Pressed, this, &ADarkMageBattleCharacter::ArrowCallbackFunction, 2);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Right", IE_Pressed, this, &ADarkMageBattleCharacter::ArrowCallbackFunction, 3);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Reset", IE_Pressed, this, &ADarkMageBattleCharacter::ArrowCallbackFunction, -1);
}

void ADarkMageBattleCharacter::ArrowCallbackFunction(int i) {
	if (arrowCallback != nullptr) {
		arrowCallback(i);
	}
}