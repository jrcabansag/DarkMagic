// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/Object.h"
#include "BattleCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAttack::AAttack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	SetSpeed();
}

void AAttack::Init(ABattleCharacter* initSpawnCharacter, ABattleCharacter* initTargetCharacter)
{
	spawnCharacter = initSpawnCharacter;
	targetCharacter = initTargetCharacter;
	FVector spawnCharacterLocation = spawnCharacter->GetActorLocation();
	SetActorLocation(spawnCharacterLocation + SPAWN_OFFSET);
	FVector targetCharacterLocation = targetCharacter->GetActorLocation();
	FVector difference = targetCharacterLocation - spawnCharacterLocation;
	difference.Normalize();
	float attackRotation = UKismetMathLibrary::DegAcos(difference.X);
	if (difference.Z < 0) {
		attackRotation = 360.0f - attackRotation;
	}
	FRotator attackRotator = FRotator(attackRotation, 0.0f, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("ACOS IS %lf"), attackRotation);
	/*FVector attackRotation = UKismetMathLibrary::FindLookAtRotation(spawnCharacterLocation, targetCharacterLocation).Vector();*/
	SetActorRotation(attackRotator);
	FVector velocityDirection = FVector(1.0f, 0.0f, 0.0f);
	ProjectileMovementComponent->SetVelocityInLocalSpace(PROJECTILE_SPEED*velocityDirection);
}

// Called when the game starts or when spawned
void AAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABattleCharacter* AAttack::GetTargetCharacter()
{
	return targetCharacter;
}

int AAttack::GetDamage()
{
	return DAMAGE;
}

void AAttack::Die()
{
	Destroy();
}

void AAttack::SetSpeed()
{
	ProjectileMovementComponent->InitialSpeed = PROJECTILE_SPEED;
	ProjectileMovementComponent->MaxSpeed = PROJECTILE_SPEED;
}

void AAttack::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetSpeed();
}

UAnimMontage* AAttack::GetAnimMontage()
{
	return animMontage;
}

