// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

void ABattleGameMode::StartPlay()
{
    Super::StartPlay();

    FStringClassReference battleWidgetClassRef(TEXT("/Game/BattleHUD.BattleHUD_C"));
    if (UClass* battleWidgetClass = battleWidgetClassRef.TryLoadClass<UUserWidget>()) {
        UE_LOG(LogTemp, Warning, TEXT("LOADED HUD"));
        battleWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), battleWidgetClass);
        if (battleWidget) {
            battleWidget->AddToViewport();
            FName arrowTextName = FName(TEXT("ArrowText"));
            UTextBlock* arrowText = (UTextBlock*)(battleWidget->WidgetTree->FindWidget(arrowTextName));
            if (arrowText != nullptr) {
                arrowText->SetText(FText::FromString(TEXT("DOGG")));
            }
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("DIDNT LOAD HUD"));
    }

    arrows = FString(TEXT("This is my test FString."));
}

void ABattleGameMode::AddArrows(FString newArrows) {
    arrows += newArrows;
}

FText ABattleGameMode::GetArrows() const {
    return FText::FromString(arrows);
}