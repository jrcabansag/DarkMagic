// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageText.h"
#include <functional>
#include "kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADamageText::ADamageText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
		WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		//WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
		WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		//WidgetComponent->SetDrawSize(FVector2D(1500.0f, 900.0f));
		WidgetComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void ADamageText::BeginPlay()
{
	Super::BeginPlay();
	//damageWidget = CreateWidget<UUserWidget>(this->GetGameInstance(), DAMAGE_WIDGET);
	//if (damageWidget) {
	//	damageWidget->SetPositionInViewport(FVector2D(100.f, 100.f));
	//	damageWidget->AddToViewport();
	//	if (FloatingText) {
	//		UE_LOG(LogTemp, Warning, TEXT("FLOATED TEXT"));
	//		damageWidget->PlayAnimation(FloatingText);
	//	}
	//	else {
	//		UE_LOG(LogTemp, Warning, TEXT("NO FLOATING TEXT"));
	//	}
	//	//UWidgetAnimation* widgetAnimation = damageWidget->animation
	//	//widgetAnimation->AnimationMap.
	//	//damageWidget->PlayAnimation(UWi)
	//}
}

void ADamageText::Init(int damage, FVector2D renderScale)
{
	if (DAMAGE_TEXT_WIDGET) {
		damageTextWidget = CreateWidget<UDamageTextWidget>(this->GetGameInstance(), DAMAGE_TEXT_WIDGET);
		WidgetComponent->SetWidget(damageTextWidget);
		std::function<void()> dieCallback = [this]() {
			Destroy();
		};
		damageTextWidget->Init(damage, dieCallback);
		damageTextWidget->SetRenderScale(renderScale);
		WidgetComponent->RegisterComponent();
		WidgetComponent->SetVisibility(true);
	}
}

// Called every frame
void ADamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector cameraLocation = UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget()->GetActorLocation();
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), cameraLocation);
	SetActorRotation(lookAtRotation);
}

