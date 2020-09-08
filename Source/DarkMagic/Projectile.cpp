// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/Object.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshBeginOverlap);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->InitialSpeed = PROJECTILE_SPEED;
	ProjectileMovementComponent->MaxSpeed = PROJECTILE_SPEED;
}

void AProjectile::Init(ABattleCharacter* initSpawnCharacter, ABattleCharacter* initTargetCharacter, std::function<void(int)> initDamageCallback)
{
	spawnCharacter = initSpawnCharacter;
	targetCharacter = initTargetCharacter;
	FVector spawnCharacterLocation = spawnCharacter->GetActorLocation();
	SetActorLocation(spawnCharacterLocation + SPAWN_OFFSET);
	damageCallback = initDamageCallback;
	FVector targetCharacterLocation = targetCharacter->GetActorLocation();
	FVector velocity = targetCharacterLocation-spawnCharacterLocation;
	ProjectileMovementComponent->SetVelocityInLocalSpace(PROJECTILE_SPEED*velocity.GetSafeNormal(1.0f));
}

void AProjectile::OnMeshBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (targetCharacter && (ABattleCharacter*)otherActor == targetCharacter) {
		if (damageCallback) {
			damageCallback(DAMAGE);
		}
		Destroy();
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

