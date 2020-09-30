// Fill out your copyright notice in the Description page of Project Settings.nim


#include "AttackAnimNotify.h"
#include "BattleCharacter.h"

void UAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
	ABattleCharacter* battleCharacter = (ABattleCharacter*)(MeshComp->GetOwner());
	if (battleCharacter != nullptr && battleCharacter->HasActorBegunPlay()) {
		battleCharacter->NotifyToAttack();
	}
}
