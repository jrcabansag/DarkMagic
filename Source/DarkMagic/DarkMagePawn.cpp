// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMagePawn.h"

// Sets default values
ADarkMagePawn::ADarkMagePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void ADarkMagePawn::BeginPlay()
{
	Super::BeginPlay();
	battleGameMode = (ABattleGameMode*)(GetWorld()->GetAuthGameMode());
}

void ADarkMagePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADarkMagePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &ADarkMagePawn::Up);
	PlayerInputComponent->BindAction("Down", IE_Pressed, this, &ADarkMagePawn::Down);
	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &ADarkMagePawn::Left);
	PlayerInputComponent->BindAction("Right", IE_Pressed, this, &ADarkMagePawn::Right);
}

void ADarkMagePawn::Up() {
	battleGameMode->PressedArrow(0);
}

void ADarkMagePawn::Down() {
	battleGameMode->PressedArrow(1);
}

void ADarkMagePawn::Left() {
	battleGameMode->PressedArrow(2);
}

void ADarkMagePawn::Right() {
	battleGameMode->PressedArrow(3);
}

