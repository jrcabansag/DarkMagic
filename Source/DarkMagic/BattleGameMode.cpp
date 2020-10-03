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
    FindWorld();
    FindHUD();
    FindPlayer();
    FindEnemy();
    InitPlayer();
    InitEnemy();
    SetUpArrowCommands(true);
}

void ABattleGameMode::FindWorld()
{
    world = GetWorld();
}

void ABattleGameMode::FindHUD()
{
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

void ABattleGameMode::FindPlayer()
{
    player = (APlayerBattleCharacter*)UGameplayStatics::GetPlayerCharacter(world, 0);
}

void ABattleGameMode::FindEnemy()
{
    TArray<AActor*> enemyArray;
    UGameplayStatics::GetAllActorsOfClass(world, AEnemyBattleCharacter::StaticClass(), enemyArray);
    if (enemyArray.Num() > 0) {
        enemy = (AEnemyBattleCharacter*)enemyArray[0];
    }
}

void ABattleGameMode::InitPlayer()
{
    UE_LOG(LogTemp, Warning, TEXT("BATTLE GAME MODE INITED PLAYER"));
    if (player) {
        std::function<void(int, int)> playerUpdateHealthUI = [this](int playerCurrentHealth, int playerTotalHealth) {
            UpdateHealthUI((ABattleCharacter*)player, playerCurrentHealth, playerTotalHealth);
        };
        std::function<void(int)> playerArrowCallback = [this](int i) {
            PressedArrow(i);
        };
        std::function<void(int)> hitCallback = [this](int i) {
            SpawnDamageText(i, (ABattleCharacter*)player, FVector2D(0.7f, 0.7f));
        };
        player->Init((ABattleCharacter*)enemy, playerUpdateHealthUI, playerArrowCallback, hitCallback);
    }
}

void ABattleGameMode::InitEnemy() {
    UE_LOG(LogTemp, Warning, TEXT("BATTLE GAME MODE INITED ENEMY"));
    if (enemy) {
        std::function<void(int, int)> enemyUpdateHealthUI = [this](int enemyCurrentHealth, int enemyTotalHealth) {
            UpdateHealthUI((ABattleCharacter*)enemy, enemyCurrentHealth, enemyTotalHealth);
        };
        std::function<void(int)> hitCallback = [this](int i) {
            SpawnDamageText(i, (ABattleCharacter*)enemy, FVector2D(1.0f, 1.0f));
        };
        enemy->Init((ABattleCharacter*)player, enemyUpdateHealthUI, hitCallback);
    }
}

void ABattleGameMode::UpdateHealthUI(ABattleCharacter* battleCharacter, int currentHealth, int totalHealth)
{
    bool isBattleCharacterPlayer = battleCharacter == (ABattleCharacter*)player;
    FString healthString = FString::Printf(TEXT("%d/%d"), currentHealth, totalHealth);
    UTextBlock* healthText = isBattleCharacterPlayer ? playerHealthText : enemyHealthText;
    UProgressBar* healthBar = isBattleCharacterPlayer ? playerHealthBar : enemyHealthBar;
    healthText->SetText(FText::FromString(healthString));
    healthBar->SetPercent(float(currentHealth) / float(totalHealth));
}

void ABattleGameMode::SpawnDamageText(int damage, ABattleCharacter* damagedCharacter, FVector2D renderScale)
{
    //UDamageTextWidget* damageTextWidget = CreateWidget<UDamageTextWidget>(this->GetGameInstance(), DAMAGE_TEXT_WIDGET);
    //damageTextWidget->Init(damage);
    //UWidgetComponent* widgetComponent = NewObject<UWidgetComponent>(UWidgetComponent::StaticClass(), UWidgetComponent::StaticClass(), FName("WidgetComponent"));
    //damageTextWidget->SetPositionInViewport(FVector2D(100.f, 100.f));
    //damageTextWidget->AddToViewport();
    ADamageText* damageText = world->SpawnActor<ADamageText>(DAMAGE_TEXT);
    damageText->Init(damage, renderScale);
    FVector damagedLocation = damagedCharacter->GetActorLocation();
    damageText->SetActorLocation(FVector(damagedLocation.X, damagedLocation.Y, damagedLocation.Z+100.f));
    //damageText->AttachToActor(damagedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
    //damageText->SetActorLocation(damagedCharacter->GetActorLocation());
}

void ABattleGameMode::PlayerAttack() {
    UE_LOG(LogTemp, Warning, TEXT("PLAYER ATTACKING!!!!!!!!!!!!!!!!!!!"));
    currentArrowCommandIndex = RESETTING_ARROW_INDEX;
    player->ShootAttack();
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
                if (isWildcard) {
                    player->StartAttack();
                }
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
    player->StopAttack();
}

