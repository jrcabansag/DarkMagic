// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Containers/Array.h"
#include "BattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DARKMAGIC_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
	const TArray<const wchar_t*> arrowTexturesReferences = {TEXT("/Game/Images/UpArrow.UpArrow"), TEXT("/Game/Images/DownArrow.DownArrow"), TEXT("/Game/Images/LeftArrow.LeftArrow") , TEXT("/Game/Images/RightArrow.RightArrow") };
	TArray<UTexture2D*> arrowTextures;
public:
	void LoadArrowTextures();
	void LoadArrowBox();
	void AddArrow(int arrowIndex);
	UHorizontalBox* arrowBox;
};
