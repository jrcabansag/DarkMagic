// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMagicianPawn.h"

// Sets default values
ADarkMagicianPawn::ADarkMagicianPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ADarkMagicianPawn::BeginPlay()
{
	Super::BeginPlay();
	battleGameMode = (ABattleGameMode*)(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ADarkMagicianPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADarkMagicianPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &ADarkMagicianPawn::Up);
	PlayerInputComponent->BindAction("Down", IE_Pressed, this, &ADarkMagicianPawn::Down);
	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &ADarkMagicianPawn::Left);
	PlayerInputComponent->BindAction("Right", IE_Pressed, this, &ADarkMagicianPawn::Right);
}

void ADarkMagicianPawn::Up() {
	battleGameMode->PressedArrow(0);
}

void ADarkMagicianPawn::Down() {
	battleGameMode->PressedArrow(1);
}

void ADarkMagicianPawn::Left() {
	battleGameMode->PressedArrow(2);
}

void ADarkMagicianPawn::Right() {
	battleGameMode->PressedArrow(3);
}

