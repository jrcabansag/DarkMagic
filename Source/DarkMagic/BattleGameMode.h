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
#include "Projectile.h"
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
		void InitHUD();
		void SetUpArrowCommands(bool initiateArrowImages);
		void AddArrowImageToBox(UImage* arrowImage);
		void AdjustImageToTexture(UImage* arrowImage, UTexture2D* arrowTexture);
		void IncorrectArrowPressed();
		int RESETTING_ARROW_INDEX = 1000;
		UProgressBar* playerHealthBar;
		UProgressBar* enemyHealthBar;
		UTextBlock* playerHealthText;
		UTextBlock* enemyHealthText;
		void UpdateHealthUI();

		//World Logic
		UWorld* world;
		void InitWorld();

		//Battle Logic
		ADarkMageBattleCharacter* player;
		AEnemyBattleCharacter* enemy;
		void InitPlayer();
		void InitEnemy();
		void PlayerAttack();
		void EnemyAttack();
		void DamagePlayer(int damage);
		void DamageEnemy(int damage);
		int playerHealth;
		int enemyHealth;
		int PLAYER_TOTAL_HEALTH;
		int ENEMY_TOTAL_HEALTH;
		UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> PLAYER_PROJECTILE;
		UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> ENEMY_PROJECTILE;
		FTimerHandle enemyAttackTimerHandle;
		UPROPERTY(EditAnywhere)
		float ENEMY_ATTACK_TIMER_DURATION = 5.0f;

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
