// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextWidget.h"

UDamageTextWidget::UDamageTextWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDamageTextWidget::Init(int damage, std::function<void()> initDieCallback)
{
	/*SetPositionInViewport(FVector2D(100.f, 100.f));
	AddToViewport();*/
	dieCallback = initDieCallback;
	DamageText->SetText(FText::AsNumber(damage));
	PlayAnimation(FloatAnimation);
	FTimerDelegate damageTimerDelegate = FTimerDelegate::CreateUObject(this, &UDamageTextWidget::Die);
	GetWorld()->GetTimerManager().SetTimer(damageTimerHandle, damageTimerDelegate, FloatAnimation->GetEndTime(), false);
}

void UDamageTextWidget::Die()
{
	dieCallback();
	//RemoveFromViewport();
}