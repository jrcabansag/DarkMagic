// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Internationalization/Text.h"

void ABattleGameMode::StartPlay()
{
    Super::StartPlay();
    InitWorld();
    InitPlayer();
    InitEnemy();
    InitHUD();
    UpdateHealthUI();
    SetUpArrowCommands(true);
}

void ABattleGameMode::InitWorld() {
    world = GetWorld();
}

void ABattleGameMode::InitEnemy() {
    TArray<AActor*> enemyArray;
    UGameplayStatics::GetAllActorsOfClass(world, AEnemyBattleCharacter::StaticClass(), enemyArray);
    if (enemyArray.Num() > 0) {
        enemy = (AEnemyBattleCharacter*)enemyArray[0];
    }
    ENEMY_TOTAL_HEALTH = enemy->TOTAL_HEALTH;
    enemyHealth = ENEMY_TOTAL_HEALTH;
    FTimerDelegate enemyAttackTimerDelegate = FTimerDelegate::CreateUObject(this, &ABattleGameMode::EnemyAttack);
    world->GetTimerManager().SetTimer(enemyAttackTimerHandle, enemyAttackTimerDelegate, ENEMY_ATTACK_TIMER_DURATION, true);
}

void ABattleGameMode::InitHUD() {
    UUserWidget* battleHUD = CreateWidget<UUserWidget>(this->GetGameInstance(), BATTLE_HUD);
    if (battleHUD) {
        battleHUD->AddToViewport();
        arrowBox = (UHorizontalBox*)(battleHUD->WidgetTree->FindWidget(FName("ArrowBox")));
        playerHealthBar = (UProgressBar*)(battleHUD->WidgetTree->FindWidget(FName("PlayerHealthBar")));
        playerHealthText = (UTextBlock*)(battleHUD->WidgetTree->FindWidget(FName("PlayerHealthText")));
        enemyHealthBar = (UProgressBar*)(battleHUD->WidgetTree->FindWidget(FName("EnemyHealthBar")));
        enemyHealthText = (UTextBlock*)(battleHUD->WidgetTree->FindWidget(FName("EnemyHealthText")));
    }
}

void ABattleGameMode::UpdateHealthUI() {
    int clampedPlayerHealth = FMath::Clamp(playerHealth, 0, PLAYER_TOTAL_HEALTH);
    int clampedEnemyHealth = FMath::Clamp(enemyHealth, 0, ENEMY_TOTAL_HEALTH);
    FString playerHealthString = FString::Printf(TEXT("%d/%d"), clampedPlayerHealth, PLAYER_TOTAL_HEALTH);
    FString enemyHealthString = FString::Printf(TEXT("%d/%d"), clampedEnemyHealth, ENEMY_TOTAL_HEALTH);
    playerHealthText->SetText(FText::FromString(playerHealthString));
    enemyHealthText->SetText(FText::FromString(enemyHealthString));
    playerHealthBar->SetPercent(float(clampedPlayerHealth) / float(PLAYER_TOTAL_HEALTH));
    enemyHealthBar->SetPercent(float(clampedEnemyHealth) / float(ENEMY_TOTAL_HEALTH));
}

UImage* ABattleGameMode::InitArrowImage(int arrowIndex) {
    UE_LOG(LogTemp, Warning, TEXT("ARROW TEXTURES SIZE IS %d"), ARROW_TEXTURES.Num());
    UTexture2D* arrowTexture = ARROW_TEXTURES[arrowIndex];
    UImage* arrowImage = NewObject<UImage>(UImage::StaticClass());
    FVector2D arrowDimensions = FVector2D(arrowTexture->GetSizeX()*ARROW_SCALE, arrowTexture->GetSizeY()*ARROW_SCALE);
    arrowImage->SetVisibility(ESlateVisibility::Visible);
    arrowImage->SetBrushSize(arrowDimensions);
    AdjustImageToTexture(arrowImage, arrowTexture);
    return arrowImage;
}

void ABattleGameMode::AdjustImageToTexture(UImage* arrowImage, UTexture2D* arrowTexture) {
    //UE_LOG(LogTemp, Warning, TEXT("ADJUSTING IMAGE %p TO TEXTURE %p"), arrowImage, arrowTexture);
    arrowImage->SetBrushFromTexture(arrowTexture);
}

void ABattleGameMode::AddArrowImageToBox(UImage* arrowImage) {
    if (arrowBox != nullptr) {
        UHorizontalBoxSlot* arrowBoxSlot = arrowBox->AddChildToHorizontalBox(arrowImage);
        FMargin arrowBoxSlotPadding = FMargin(ARROW_PADDING, 0, ARROW_PADDING, 0);
        arrowBoxSlot->SetVerticalAlignment(VAlign_Center);
        arrowBoxSlot->SetPadding(arrowBoxSlotPadding);
    }
}

void ABattleGameMode::PressedArrow(int arrowIndex) {
    UE_LOG(LogTemp, Warning, TEXT("PRESSED ARROW %d"), arrowIndex);
    if (arrowBox != nullptr) {
        if (arrowIndex < 0) {
            IncorrectArrowPressed();
            return;
        }
        if (currentArrowCommandIndex < ARROW_COMMANDS_SIZE) {
            int correctArrowCommand = arrowCommands[currentArrowCommandIndex];
            bool isWildcard = correctArrowCommand == ARROW_TEXTURES.Num()-1;
            if (isWildcard || correctArrowCommand == arrowIndex) {
                UImage* arrowImage = arrowCommandImages[currentArrowCommandIndex];
                //UE_LOG(LogTemp, Warning, TEXT("GOT ARROW IMAGE"));
                UTexture2D* arrowTexture = ARROW_PRESSED_TEXTURES[arrowIndex];
                //UE_LOG(LogTemp, Warning, TEXT("GOT ARROW TEXTURE"), arrowIndex);
                AdjustImageToTexture(arrowImage, arrowTexture);
                currentArrowCommandIndex++;
            } else {
                IncorrectArrowPressed();
                return;
            }
        }
        if (currentArrowCommandIndex >= ARROW_COMMANDS_SIZE && currentArrowCommandIndex != RESETTING_ARROW_INDEX) {
            PlayerAttack();
            FTimerDelegate resetArrowTimerDelegate = FTimerDelegate::CreateUObject(this, &ABattleGameMode::SetUpArrowCommands, false);
            world->GetTimerManager().SetTimer(resetArrowTimerHandle, resetArrowTimerDelegate, RESET_ARROW_TIMER_DURATION, false);
        }
    }
}

void ABattleGameMode::PlayerAttack() {
    UE_LOG(LogTemp, Warning, TEXT("PLAYER ATTACKING!!!!!!!!!!!!!!!!!!!"));
    currentArrowCommandIndex = RESETTING_ARROW_INDEX;
    if (PLAYER_PROJECTILE) {
        AProjectile* projectile = world->SpawnActor<AProjectile>(PLAYER_PROJECTILE);
        projectile->Init(player, enemy, [this] (int damage) {
            DamageEnemy(damage);
        });
    }
}

void ABattleGameMode::EnemyAttack() {
    UE_LOG(LogTemp, Warning, TEXT("ENEMY ATTACKING!!!!!!!!!!!!!!!!!!!"));
    if (ENEMY_PROJECTILE) {
        AProjectile* projectile = world->SpawnActor<AProjectile>(ENEMY_PROJECTILE);
        projectile->Init(enemy, player, [this](int damage) {
            DamagePlayer(damage);
        });
    }
}

void ABattleGameMode::DamagePlayer(int damage) {
    UE_LOG(LogTemp, Warning, TEXT("DAMAGED PLAYER FOR %d"), damage);
    playerHealth -= damage;
    UpdateHealthUI();
}

void ABattleGameMode::DamageEnemy(int damage) {
    UE_LOG(LogTemp, Warning, TEXT("DAMAGED ENEMY FOR %d"), damage);
    enemyHealth -= damage;
    UpdateHealthUI();
}

void ABattleGameMode::SetUpArrowCommands(bool initiateArrowImages) {
    UE_LOG(LogTemp, Warning, TEXT("SETTING ARROW COMMANDS"));
    for (int x = 0; x < ARROW_COMMANDS_SIZE; x++) {
        int arrowIndex = x == 0 ?
            ARROW_TEXTURES.Num()-1 : FMath::RandRange(0, ARROW_PRESSED_TEXTURES.Num() - 1);
        if (initiateArrowImages) {
            UImage* arrowImage = InitArrowImage(arrowIndex);
            AddArrowImageToBox(arrowImage);
            arrowCommandImages.Add(arrowImage);
            arrowCommands.Add(arrowIndex);
        } else {
            UImage* arrowImage = arrowCommandImages[x];
            UTexture2D* arrowTexture = ARROW_TEXTURES[arrowIndex];
            AdjustImageToTexture(arrowImage, arrowTexture);
            arrowCommands[x] = arrowIndex;
        }
    }
    currentArrowCommandIndex = 0;
}

void ABattleGameMode::IncorrectArrowPressed() {
    for (int x = currentArrowCommandIndex-1; x >= 0; x--) {
        UImage* arrowImage = arrowCommandImages[x];
        UTexture2D* arrowTexture = ARROW_TEXTURES[arrowCommands[x]];
        AdjustImageToTexture(arrowImage, arrowTexture);
    }
    currentArrowCommandIndex = 0;
}

void ABattleGameMode::InitPlayer() {
    UE_LOG(LogTemp, Warning, TEXT("BATTLE GAME MODE INITED PLAYER"));
    player = (ADarkMageBattleCharacter*)UGameplayStatics::GetPlayerCharacter(world, 0);
    if (player) {
        player->arrowCallback = [this](int i) {
            PressedArrow(i);
        };
    }
    PLAYER_TOTAL_HEALTH = player->TOTAL_HEALTH;
    playerHealth = PLAYER_TOTAL_HEALTH;
}

