// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Blueprint/WidgetTree.h"

void ABattleGameMode::StartPlay()
{
    Super::StartPlay();
    LoadArrowTextures();
    LoadArrowBox();
}

void ABattleGameMode::LoadArrowBox() {
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

void ABattleGameMode::LoadArrowTextures() {
    for (int x = 0; x < arrowTexturesReferences.Num(); x++) {
        arrowTextures.Add(LoadObject<UTexture2D>(NULL, arrowTexturesReferences[x], NULL, LOAD_None, NULL));
    }
}

void ABattleGameMode::AddArrow(int arrowIndex) {
    if (arrowBox != nullptr) {
        UTexture2D* arrowTexture = arrowTextures[arrowIndex];
        UImage* arrowImage = NewObject<UImage>(UImage::StaticClass());
        FVector2D upArrowDimensions = FVector2D(arrowTexture->GetSizeX()/2, arrowTexture->GetSizeY()/2);
        arrowImage->SetBrushSize(upArrowDimensions);
        arrowImage->SetVisibility(ESlateVisibility::Visible);
        arrowImage->SetBrushFromTexture(arrowTexture);
        UHorizontalBoxSlot* arrowBoxSlot = arrowBox->AddChildToHorizontalBox(arrowImage);
        FMargin arrowBoxSlotPadding = FMargin(10, 0, 10, 0);
        arrowBoxSlot->SetVerticalAlignment(VAlign_Center);
        arrowBoxSlot->SetPadding(arrowBoxSlotPadding);
    }
}