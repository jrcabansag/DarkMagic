// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCharacter.h"
#include "Engine/SkeletalMesh.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/Object.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattleCharacter::ABattleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentHealth = TOTAL_HEALTH;
	if (this) {
		UCharacterMovementComponent* characterMovementComponent = GetCharacterMovement();
		if (characterMovementComponent) {
			characterMovementComponent->DefaultLandMovementMode = MOVE_Flying;
		}
		USkeletalMeshComponent* meshComponent = GetMesh();
		leftHandParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(FName("LeftHandParticles"));
		leftHandParticleSystem->AttachToComponent(meshComponent, FAttachmentTransformRules::KeepRelativeTransform, FName("LowerHand_L"));
		rightHandParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(FName("RightHandParticles"));
		rightHandParticleSystem->AttachToComponent(meshComponent, FAttachmentTransformRules::KeepRelativeTransform, FName("LowerHand_R"));
	}
}

// Called when the game starts or when spawned
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMeshComponent* meshComponent = GetMesh();
}

void ABattleCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (this) {
		FVector currentLocation = GetActorLocation();
		SetActorLocation(FVector(currentLocation.X, currentLocation.Y, MESH_HEIGHT / 2));
		USkeletalMeshComponent* meshComponent = GetMesh();
		if (meshComponent) {
			FVector meshLocation = FVector(0.0f, 0.0f, -MESH_HEIGHT / 2);
			meshComponent->SetRelativeLocation(meshLocation);
			UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
			if (capsuleComponent) {
				capsuleComponent->SetCapsuleHalfHeight(MESH_HEIGHT / 2);
				capsuleComponent->SetCapsuleRadius(MESH_RADIUS);
			}
			if (HAND_PARTICLES) {
				leftHandParticleSystem->SetTemplate(HAND_PARTICLES);
				rightHandParticleSystem->SetTemplate(HAND_PARTICLES);
				leftHandParticleSystem->SetRelativeLocation(HAND_PARTICLE_LOCATION);
				leftHandParticleSystem->SetRelativeScale3D(FVector(0.01*HAND_PARTICLE_SCALE, 0.01*HAND_PARTICLE_SCALE, 0.01*HAND_PARTICLE_SCALE));
				rightHandParticleSystem->SetRelativeLocation(HAND_PARTICLE_LOCATION);
				rightHandParticleSystem->SetRelativeScale3D(FVector(0.01 *HAND_PARTICLE_SCALE, 0.01 *HAND_PARTICLE_SCALE, 0.01 *HAND_PARTICLE_SCALE));
			}
		}
	}
}
// Called every frame
void ABattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
