// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Containers/Array.h"
#include "Blueprint/UserWidget.h"
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
		const float RESET_ARROW_TIMER_DURATION = 0.2f;

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
		ABattleGameMode();
		void PressedArrow(int arrowIndex);
		UPROPERTY(EditAnywhere)
		TArray<UTexture2D*> arrowTextures;
		UPROPERTY(EditAnywhere)
		TArray<UTexture2D*> arrowPressedTextures;
		UPROPERTY(EditAnywhere)
		int ARROW_COMMANDS_SIZE;
		UPROPERTY(EditAnywhere)
		UClass* battleWidgets;
		UPROPERTY(EditAnywhere)
		float ARROW_SCALE;
		UPROPERTY(EditAnywhere)
		float ARROW_PADDING;
};
