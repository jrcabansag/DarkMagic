// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMagicianPawn.h"
#include "BattleGameMode.h"

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

	UE_LOG(LogTemp, Warning, TEXT("DARK MAGICIAN PAWN SPAWNED 3!"));
	
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
	UE_LOG(LogTemp, Warning, TEXT("DARK MAGICIAN PAWN SET INPUT!"));
	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &ADarkMagicianPawn::Jump);
}

void ADarkMagicianPawn::Jump() {
	ABattleGameMode* battleGameMode = Cast<ABattleGameMode>(GetWorld()->GetAuthGameMode());
	battleGameMode->AddArrows("UP");
	UE_LOG(LogTemp, Warning, TEXT("JUMPED!"));
}

