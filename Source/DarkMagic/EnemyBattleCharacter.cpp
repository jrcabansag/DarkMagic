// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBattleCharacter.h"

void AEnemyBattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate attackTimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemyBattleCharacter::Attack);
	world->GetTimerManager().SetTimer(attackTimerHandle, attackTimerDelegate, ATTACK_TIMER_DURATION, true);
}

