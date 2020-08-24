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
    InitArrowCommands();
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
        arrowPressedTextures.Add(LoadObject<UTexture2D>(NULL, ARROW_PRESSED_TEXTURES_REFERENCES[x], NULL, LOAD_None, NULL));
    }
}

void ABattleGameMode::InitArrowCommands() {
    for (int x = 0; x < ARROW_COMMANDS_SIZE; x++) {
        int arrowIndex = FMath::RandRange(0, ARROW_TEXTURES_REFERENCES.Num() - 1);
        UImage* arrowImage = InitArrowImage(arrowIndex);
        AddArrowImageToBox(arrowImage);
        arrowCommands.Add(arrowIndex);
        arrowCommandImages.Add(arrowImage);
    }
}

UImage* ABattleGameMode::InitArrowImage(int arrowIndex) {
    UTexture2D* arrowTexture = arrowTextures[arrowIndex];
    UImage* arrowImage = NewObject<UImage>(UImage::StaticClass());
    AdjustImageToTexture(arrowImage, arrowTexture);
    return arrowImage;
}

void ABattleGameMode::AdjustImageToTexture(UImage* arrowImage, UTexture2D* arrowTexture) {
    FVector2D arrowDimensions = FVector2D(arrowTexture->GetSizeX() / 2, arrowTexture->GetSizeY() / 2);
    arrowImage->SetBrushSize(arrowDimensions);
    arrowImage->SetVisibility(ESlateVisibility::Visible);
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
        if (currentArrowCommandIndex < ARROW_COMMANDS_SIZE) {
            if (arrowCommands[currentArrowCommandIndex] == arrowIndex) {
                arrowCommandImages[currentArrowCommandIndex]->SetBrushFromTexture(arrowPressedTextures[arrowIndex]);
                currentArrowCommandIndex++;
            }
        }
        if (currentArrowCommandIndex >= ARROW_COMMANDS_SIZE) {
            ResetArrowCommands();
        }
    }
}

void ABattleGameMode::ResetArrowCommands() {
    for (int x = 0; x < ARROW_COMMANDS_SIZE; x++) {
        int arrowIndex = FMath::RandRange(0, ARROW_TEXTURES_REFERENCES.Num() - 1);
        UImage* arrowImage = arrowCommandImages[x];
        UTexture2D* arrowTexture = arrowTextures[arrowIndex];
        AdjustImageToTexture(arrowImage, arrowTexture);
        arrowCommands[x] = arrowIndex;
    }
    currentArrowCommandIndex = 0;
}

