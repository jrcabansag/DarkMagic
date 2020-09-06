// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/Object.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattleCharacter::ABattleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	currentHealth = TOTAL_HEALTH;
	meshComponent = GetMesh();
	if (meshComponent) {
		InitHandParticleSystemComponent(leftHandParticleSystemComponent, FName("LeftHandParticles"), FName("LowerHand_L"));
		InitHandParticleSystemComponent(rightHandParticleSystemComponent, FName("RightHandParticles"), FName("LowerHand_R"));
		GetCharacterMovement()->DefaultLandMovementMode = MOVE_Flying;
	}
}

// Called when the game starts or when spawned
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HAND_PARTICLES) {
		SetUpHandParticleSystemComponent(leftHandParticleSystemComponent);
		SetUpHandParticleSystemComponent(rightHandParticleSystemComponent);
	}
	leftHandParticleSystemComponent->RegisterComponent();
	rightHandParticleSystemComponent->RegisterComponent();
}

void ABattleCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	AdjustMeshToSize();
	if (HAND_PARTICLES) {
		SetUpHandParticleSystemComponent(leftHandParticleSystemComponent);
		SetUpHandParticleSystemComponent(rightHandParticleSystemComponent);
	}
}

void ABattleCharacter::InitHandParticleSystemComponent(UParticleSystemComponent*& handParticleSystemComponent, FName componentName, FName componentToAttachToName) {
	handParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(componentName);
	handParticleSystemComponent->AttachToComponent(meshComponent, FAttachmentTransformRules::KeepRelativeTransform, componentToAttachToName);
}

void ABattleCharacter::SetUpHandParticleSystemComponent(UParticleSystemComponent* handParticleSystemComponent)
{
	handParticleSystemComponent->SetTemplate(HAND_PARTICLES);
	handParticleSystemComponent->SetRelativeLocation(HAND_PARTICLE_LOCATION);
	float handParticleScale = 0.01f * HAND_PARTICLE_SCALE;
	handParticleSystemComponent->SetRelativeScale3D(FVector(handParticleScale, handParticleScale, handParticleScale));
}

void ABattleCharacter::AdjustMeshToSize() {
	if (meshComponent) {
		FVector currentLocation = GetActorLocation();
		SetActorLocation(FVector(currentLocation.X, currentLocation.Y, MESH_HEIGHT / 2));
		FVector meshLocation = FVector(0.0f, 0.0f, -MESH_HEIGHT / 2);
		meshComponent->SetRelativeLocation(meshLocation);
		UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
		if (capsuleComponent) {
			capsuleComponent->SetCapsuleHalfHeight(MESH_HEIGHT / 2);
			capsuleComponent->SetCapsuleRadius(MESH_RADIUS);
		}
	}
}
