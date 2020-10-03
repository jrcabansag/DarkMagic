// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "TimerManager.h"
#include <functional>
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class DARKMAGIC_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UDamageTextWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText;
	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* FloatAnimation;
	void Init(int damage, std::function<void()> initDieCallback);
	FTimerHandle damageTimerHandle;
	void Die();
	std::function<void()> dieCallback;
	//FVector GetTextWorldLocation();
};
