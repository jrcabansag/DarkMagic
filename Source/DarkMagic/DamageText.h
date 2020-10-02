// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTextWidget.h"
#include "Components/WidgetComponent.h"
#include "DamageText.generated.h"

UCLASS()
class DARKMAGIC_API ADamageText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init(int damage);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageTextWidget> DAMAGE_TEXT_WIDGET;
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent;
	UDamageTextWidget* damageTextWidget;
};
