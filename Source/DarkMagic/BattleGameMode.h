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
	private:
		virtual void StartPlay() override;

		const TArray<const wchar_t*> ARROW_TEXTURES_REFERENCES = {
			TEXT("/Game/Images/UpArrow.UpArrow"), 
			TEXT("/Game/Images/DownArrow.DownArrow"), 
			TEXT("/Game/Images/LeftArrow.LeftArrow"), 
			TEXT("/Game/Images/RightArrow.RightArrow"),
			TEXT("/Game/Images/Wildcard.Wildcard")
		};
		const TArray<const wchar_t*> ARROW_PRESSED_TEXTURES_REFERENCES = {
			TEXT("/Game/Images/UpArrowPressed.UpArrowPressed"),
			TEXT("/Game/Images/DownArrowPressed.DownArrowPressed"),
			TEXT("/Game/Images/LeftArrowPressed.LeftArrowPressed"),
			TEXT("/Game/Images/RightArrowPressed.RightArrowPressed")
		};
		const int ARROW_COMMANDS_SIZE = 5;
		const float RESET_ARROW_TIMER_DURATION = 0.2f;

		TArray<UTexture2D*> arrowTextures;
		TArray<UTexture2D*> arrowPressedTextures;
		UHorizontalBox* arrowBox;
		TArray<int> arrowCommands;
		TArray<UImage*> arrowCommandImages;
		int currentArrowCommandIndex;
		UImage* InitArrowImage(int arrowIndex);
		FTimerHandle resetArrowTimerHandle;

		void InitArrowTextures();
		void InitArrowBox();
		//void InitArrowCommands();
		void AddArrowImageToBox(UImage* arrowImage);
		void AdjustImageToTexture(UImage* arrowImage, UTexture2D* arrowTexture);
		void IncorrectArrowPressed();
		UFUNCTION()
		void SetUpArrowCommands(bool initiateArrowImages);

	public:
		void PressedArrow(int arrowIndex);
};
