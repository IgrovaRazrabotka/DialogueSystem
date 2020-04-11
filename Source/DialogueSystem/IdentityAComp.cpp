// Fill out your copyright notice in the Description page of Project Settings.

#include "IdentityAComp.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TextBlock.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UIdentityAComp::UIdentityAComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/WorldIdentifierText"));
	if (WidgetClassFinder.Succeeded())
	{
		WidgetClass = WidgetClassFinder.Class;
	}
	// ...
}


// Called when the game starts
void UIdentityAComp::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		Widget = NewObject<UWidgetComponent>(GetOwner());
		Widget->RegisterComponent();
		Widget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Widget->SetWidgetSpace(EWidgetSpace::Screen);
		Widget->SetWidgetClass(WidgetClass);
		UUserWidget* UserWidget = Widget->GetUserWidgetObject();
		UTextBlock* TextBlock = Cast<UTextBlock>(UserWidget->GetWidgetFromName(TEXT("Text")));
		TextBlock->SetText(Name);
		Hide();
	}
}


// Called every frame
void UIdentityAComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UIdentityAComp::Show() {
	if (Widget) {
		Widget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	}
}

void UIdentityAComp::Hide() {
	if (Widget) {
		Widget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	}
}

