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
}

void ADarkMagePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADarkMagePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("DARK MAGE PAWN SET UP PLAYER INPUT"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Up", IE_Pressed, this, &ADarkMagePawn::ArrowCallbackFunction, 0);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Down", IE_Pressed, this, &ADarkMagePawn::ArrowCallbackFunction, 1);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Left", IE_Pressed, this, &ADarkMagePawn::ArrowCallbackFunction, 2);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Right", IE_Pressed, this, &ADarkMagePawn::ArrowCallbackFunction, 3);
	PlayerInputComponent->BindAction<ArrowCallbackDelegate>("Reset", IE_Pressed, this, &ADarkMagePawn::ArrowCallbackFunction, -1);
}

void ADarkMagePawn::ArrowCallbackFunction(int i) {
	if (arrowCallback != nullptr) {
		arrowCallback(i);
	}
}