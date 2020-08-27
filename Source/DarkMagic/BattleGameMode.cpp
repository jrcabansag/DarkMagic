// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Math/UnrealMathUtility.h"

void ABattleGameMode::StartPlay()
{
    Super::StartPlay();
    InitArrowTextures();
    InitArrowBox();
    SetUpArrowCommands(true);
}

void ABattleGameMode::InitArrowBox() {
    FStringClassReference battleWidgetClassRef(TEXT("/Game/BattleHUD.BattleHUD_C"));
    if (UClass* battleWidgetClass = battleWidgetClassRef.TryLoadClass<UUserWidget>()) {
       UUserWidget* battleWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), battleWidgetClass);
        if (battleWidget) {
            battleWidget->AddToViewport();
            FName arrowBoxName = FName(TEXT("ArrowBox"));
            arrowBox = (UHorizontalBox*)(battleWidget->WidgetTree->FindWidget(arrowBoxName));
        }
    }
}

void ABattleGameMode::InitArrowTextures() {
    for (int x = 0; x < ARROW_TEXTURES_REFERENCES.Num(); x++) {
        arrowTextures.Add(LoadObject<UTexture2D>(NULL, ARROW_TEXTURES_REFERENCES[x], NULL, LOAD_None, NULL));
    }
    for (int x = 0; x < ARROW_PRESSED_TEXTURES_REFERENCES.Num(); x++) {
        arrowPressedTextures.Add(LoadObject<UTexture2D>(NULL, ARROW_PRESSED_TEXTURES_REFERENCES[x], NULL, LOAD_None, NULL));
    }
}

UImage* ABattleGameMode::InitArrowImage(int arrowIndex) {
    UTexture2D* arrowTexture = arrowTextures[arrowIndex];
    UImage* arrowImage = NewObject<UImage>(UImage::StaticClass());
    FVector2D arrowDimensions = FVector2D(arrowTexture->GetSizeX() / 2, arrowTexture->GetSizeY() / 2);
    arrowImage->SetVisibility(ESlateVisibility::Visible);
    arrowImage->SetBrushSize(arrowDimensions);
    AdjustImageToTexture(arrowImage, arrowTexture);
    return arrowImage;
}

void ABattleGameMode::AdjustImageToTexture(UImage* arrowImage, UTexture2D* arrowTexture) {
    arrowImage->SetBrushFromTexture(arrowTexture);
}

void ABattleGameMode::AddArrowImageToBox(UImage* arrowImage) {
    if (arrowBox != nullptr) {
        UHorizontalBoxSlot* arrowBoxSlot = arrowBox->AddChildToHorizontalBox(arrowImage);
        FMargin arrowBoxSlotPadding = FMargin(10, 0, 10, 0);
        arrowBoxSlot->SetVerticalAlignment(VAlign_Center);
        arrowBoxSlot->SetPadding(arrowBoxSlotPadding);
    }
}

void ABattleGameMode::PressedArrow(int arrowIndex) {
    if (arrowBox != nullptr) {
        if (arrowIndex < 0) {
            IncorrectArrowPressed();
            return;
        }
        if (currentArrowCommandIndex < ARROW_COMMANDS_SIZE) {
            int correctArrowCommand = arrowCommands[currentArrowCommandIndex];
            bool isWildcard = correctArrowCommand == ARROW_TEXTURES_REFERENCES.Num()-1;
            if (isWildcard || correctArrowCommand == arrowIndex) {
                UImage* arrowImage = arrowCommandImages[currentArrowCommandIndex];
                UTexture2D* arrowTexture = arrowPressedTextures[arrowIndex];
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
    for (int x = 0; x < ARROW_COMMANDS_SIZE; x++) {
        int arrowIndex = x == 0 ?
            ARROW_TEXTURES_REFERENCES.Num()-1 : FMath::RandRange(0, ARROW_PRESSED_TEXTURES_REFERENCES.Num() - 1);
        if (initiateArrowImages) {
            UImage* arrowImage = InitArrowImage(arrowIndex);
            AddArrowImageToBox(arrowImage);
            arrowCommandImages.Add(arrowImage);
            arrowCommands.Add(arrowIndex);
        } else {
            UImage* arrowImage = arrowCommandImages[x];
            UTexture2D* arrowTexture = arrowTextures[arrowIndex];
            AdjustImageToTexture(arrowImage, arrowTexture);
            arrowCommands[x] = arrowIndex;
        }
    }
    currentArrowCommandIndex = 0;
}

void ABattleGameMode::IncorrectArrowPressed() {
    for (int x = currentArrowCommandIndex-1; x >= 0; x--) {
        UImage* arrowImage = arrowCommandImages[x];
        UTexture2D* arrowTexture = arrowTextures[arrowCommands[x]];
        AdjustImageToTexture(arrowImage, arrowTexture);
    }
    currentArrowCommandIndex = 0;
}

