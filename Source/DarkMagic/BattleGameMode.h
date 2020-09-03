// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Containers/Array.h"
#include "Blueprint/UserWidget.h"
#include <functional>
#include "DarkMageBattleCharacter.h"
#include "BattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DARKMAGIC_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	private:
		virtual void StartPlay() override;

		//UI
		UHorizontalBox* arrowBox;
		TArray<int> arrowCommands;
		TArray<UImage*> arrowCommandImages;
		int currentArrowCommandIndex;
		UImage* InitArrowImage(int arrowIndex);
		FTimerHandle resetArrowTimerHandle;
		void InitArrowBox();
		void SetUpArrowCommands(bool initiateArrowImages);
		void AddArrowImageToBox(UImage* arrowImage);
		void AdjustImageToTexture(UImage* arrowImage, UTexture2D* arrowTexture);
		void IncorrectArrowPressed();

		//Battle Logic
		ADarkMageBattleCharacter* player;
		void InitPlayer();
	public:
		void PressedArrow(int arrowIndex);
		UPROPERTY(EditAnywhere)
		UClass* BATTLE_HUD;
		UPROPERTY(EditAnywhere)
		TArray<UTexture2D*> ARROW_TEXTURES;
		UPROPERTY(EditAnywhere)
		TArray<UTexture2D*> ARROW_PRESSED_TEXTURES;
		UPROPERTY(EditAnywhere)
		int ARROW_COMMANDS_SIZE;
		UPROPERTY(EditAnywhere)
		float ARROW_SCALE;
		UPROPERTY(EditAnywhere)
		float ARROW_PADDING;
		UPROPERTY(EditAnywhere)
		float RESET_ARROW_TIMER_DURATION;
};
