// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "DarkMagePawn.h"

void ABattleGameMode::StartPlay()
{
    Super::StartPlay();
    InitPlayer();
    InitArrowBox();
    SetUpArrowCommands(true);
}

void ABattleGameMode::InitArrowBox() {
       UUserWidget* battleWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), battleWidgets);
        if (battleWidget) {
            battleWidget->AddToViewport();
            FName arrowBoxName = FName(TEXT("ArrowBox"));
            arrowBox = (UHorizontalBox*)(battleWidget->WidgetTree->FindWidget(arrowBoxName));
        }
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
    UE_LOG(LogTemp, Warning, TEXT("ADJUSTING IMAGE %p TO TEXTURE %p"), arrowImage, arrowTexture);
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
                UE_LOG(LogTemp, Warning, TEXT("GOT ARROW IMAGE"));
                UTexture2D* arrowTexture = ARROW_PRESSED_TEXTURES[arrowIndex];
                UE_LOG(LogTemp, Warning, TEXT("GOT ARROW TEXTURE"), arrowIndex);
                AdjustImageToTexture(arrowImage, arrowTexture);
                currentArrowCommandIndex++;
            } else {
                IncorrectArrowPressed();
                return;
            }
        }
        if (currentArrowCommandIndex >= ARROW_COMMANDS_SIZE) {
            FTimerDelegate resetArrowTimerDelegate = FTimerDelegate::CreateUObject(this, &ABattleGameMode::SetUpArrowCommands, false);
            GetWorld()->GetTimerManager().SetTimer(resetArrowTimerHandle, resetArrowTimerDelegate, RESET_ARROW_TIMER_DURATION, false);
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
}

void ABattleGameMode::InitPlayer() {
    UE_LOG(LogTemp, Warning, TEXT("BATTLE GAME MODE INITED PLAYER"));
    player = (ADarkMagePawn*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    player->arrowCallback = [this](int i) {
        PressedArrow(i);
    };
}

