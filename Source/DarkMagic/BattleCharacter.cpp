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
	MeshComponent = GetMesh();
	if (MeshComponent) {
		UCapsuleComponent* MyCapsuleComponent = GetCapsuleComponent();
		if (MyCapsuleComponent) {
			MyCapsuleComponent->SetCollisionProfileName(TEXT("OverlapAll"));
			MyCapsuleComponent->SetGenerateOverlapEvents(true);
			MyCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABattleCharacter::OnBeginOverlap);
		}
		InitHandParticleSystemComponent(LeftHandParticleSystemComponent, FName("LeftHandParticles"), FName("LowerHand_L"));
		InitHandParticleSystemComponent(RightHandParticleSystemComponent, FName("RightHandParticles"), FName("LowerHand_R"));
		GetCharacterMovement()->DefaultLandMovementMode = MOVE_Flying;
	}
	currentHealth = TOTAL_HEALTH;
}

void ABattleCharacter::Init(ABattleCharacter* initOpponent, std::function<void(int, int)> initUpdateHealthCallback)
{
	opponent = initOpponent;
	updateHealthCallback = initUpdateHealthCallback;
	if (updateHealthCallback) {
		updateHealthCallback(currentHealth, TOTAL_HEALTH);
	}
}

// Called when the game starts or when spawned
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HAND_PARTICLES) {
		SetUpHandParticleSystemComponent(LeftHandParticleSystemComponent);
		SetUpHandParticleSystemComponent(RightHandParticleSystemComponent);
	}
	LeftHandParticleSystemComponent->RegisterComponent();
	RightHandParticleSystemComponent->RegisterComponent();
	world = GetWorld();
	animInstance = MeshComponent->GetAnimInstance();
	animMontage = ((AAttack*)ATTACK->GetDefaultObject())->GetAnimMontage();
	if (STANCE_ANIM_MONTAGE) {
		animInstance->Montage_Play(STANCE_ANIM_MONTAGE);
	}
}

void ABattleCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	AdjustMeshToSize();
	if (HAND_PARTICLES) {
		SetUpHandParticleSystemComponent(LeftHandParticleSystemComponent);
		SetUpHandParticleSystemComponent(RightHandParticleSystemComponent);
	}
}

void ABattleCharacter::InitHandParticleSystemComponent(UParticleSystemComponent*& handParticleSystemComponent, FName componentName, FName componentToAttachToName) {
	handParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(componentName);
	handParticleSystemComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform, componentToAttachToName);
}

void ABattleCharacter::SetUpHandParticleSystemComponent(UParticleSystemComponent* handParticleSystemComponent)
{
	handParticleSystemComponent->SetTemplate(HAND_PARTICLES);
	handParticleSystemComponent->SetRelativeLocation(HAND_PARTICLE_LOCATION);
	float handParticleScale = 0.01f * HAND_PARTICLE_SCALE;
	handParticleSystemComponent->SetRelativeScale3D(FVector(handParticleScale, handParticleScale, handParticleScale));
}

void ABattleCharacter::AdjustMeshToSize() {
	if (MeshComponent) {
		FVector currentLocation = GetActorLocation();
		SetActorLocation(FVector(currentLocation.X, currentLocation.Y, MESH_HEIGHT / 2));
		FVector meshLocation = FVector(0.0f, 0.0f, -MESH_HEIGHT / 2);
		MeshComponent->SetRelativeLocation(meshLocation);
		UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
		if (capsuleComponent) {
			capsuleComponent->SetCapsuleHalfHeight(MESH_HEIGHT / 2);
			capsuleComponent->SetCapsuleRadius(MESH_RADIUS);
		}
	}
}

void ABattleCharacter::HitByAttack(AAttack* attack)
{
	UpdateHealth(-attack->GetDamage());
	attack->Die();
}

void ABattleCharacter::UpdateHealth(int healthChange)
{
	currentHealth += healthChange;
	currentHealth = FMath::Clamp(currentHealth, 0, TOTAL_HEALTH);
	if (updateHealthCallback) {
		updateHealthCallback(currentHealth, TOTAL_HEALTH);
	}
}

void ABattleCharacter::OnBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP MESH"));
	if (otherActor->IsA(AAttack::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP PROJECTILE"));
		AAttack* attack = (AAttack*)otherActor;
		if (attack->GetTargetCharacter() == this) {
			HitByAttack(attack);
		}
	}
}

void ABattleCharacter::StartAttack()
{
	if (animInstance) {
		if (animMontage) {
			animInstance->Montage_Play(animMontage, 1.0f);
		}
	}
}

void ABattleCharacter::ShootAttack()
{
	if (animInstance->Montage_IsPlaying(animMontage)) {
		animInstance->Montage_JumpToSection(FName("Shoot"), animMontage);
	}
	else {
		animInstance->Montage_Resume(animMontage);
	}
}

void ABattleCharacter::SpawnAttack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
	AAttack* attack = world->SpawnActor<AAttack>(ATTACK);
	attack->Init(this, opponent);
}

void ABattleCharacter::NotifyToSpawnAttack()
{
	SpawnAttack();
}

void ABattleCharacter::NotifyToPauseAttack()
{
	animInstance->Montage_Pause(animMontage);
}

void ABattleCharacter::StopAttack()
{
	animInstance->Montage_Stop(0.3f, animMontage);
}