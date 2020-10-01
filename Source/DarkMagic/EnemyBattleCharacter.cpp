// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBattleCharacter.h"

void AEnemyBattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate startAttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemyBattleCharacter::StartAttack);
	world->GetTimerManager().SetTimer(attackTimerHandle, startAttackTimerDelegate, BATTLE_START_WAITING_TIME, false);
}

void AEnemyBattleCharacter::StartAttack()
{
	Super::StartAttack();
	FTimerDelegate shootAttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemyBattleCharacter::ShootAttack);
	world->GetTimerManager().SetTimer(attackTimerHandle, shootAttackTimerDelegate, SHOOT_ATTACK_TIME, false);
}

void AEnemyBattleCharacter::ShootAttack()
{
	Super::ShootAttack();
	FTimerDelegate startAttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemyBattleCharacter::StartAttack);
	world->GetTimerManager().SetTimer(attackTimerHandle, startAttackTimerDelegate, CHOOSE_ATTACK_TIME, false);
}