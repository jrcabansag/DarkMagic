// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Containers/Array.h"
#include "Blueprint/UserWidget.h"
#include <functional>
#include "DarkMageBattleCharacter.h"
#include "EnemyBattleCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"
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

		//World Logic
		UWorld* world;
		void FindWorld();

		//Battle Logic
		ADarkMageBattleCharacter* player;
		AEnemyBattleCharacter* enemy;
		void FindPlayer();
		void FindEnemy();
		void InitPlayer();
		void InitEnemy();
		void PlayerAttack();

		//UI HUD
		UPROPERTY(EditAnywhere)
		UClass* BATTLE_HUD;
		void FindHUD();

		//UI ARROWS
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
		UHorizontalBox* arrowBox;
		TArray<int> arrowCommands;
		TArray<UImage*> arrowCommandImages;
		int currentArrowCommandIndex;
		UImage* InitArrowImage(int arrowIndex);
		void SetUpArrowCommands(bool initiateArrowImages);
		void AddArrowImageToBox(UImage* arrowImage);
		void AdjustImageToTexture(UImage* arrowImage, UTexture2D* arrowTexture);
		void IncorrectArrowPressed();
		FTimerHandle resetArrowTimerHandle;
		int RESETTING_ARROW_INDEX = 1000;
		void PressedArrow(int arrowIndex);

		//UI HEALTH
		UProgressBar* playerHealthBar;
		UProgressBar* enemyHealthBar;
		UTextBlock* playerHealthText;
		UTextBlock* enemyHealthText;
		void UpdateHealthUI(ABattleCharacter* battleCharacter, int currentHealth, int totalHealth);
};
