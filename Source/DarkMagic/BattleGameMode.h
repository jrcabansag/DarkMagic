// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class DARKMAGIC_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;

	FString arrows;
public:
	void AddArrows(FString newArrows);

	class UUserWidget* battleWidget;

	UFUNCTION(BlueprintPure, Category = "Health")
	FText GetArrows() const;
};
