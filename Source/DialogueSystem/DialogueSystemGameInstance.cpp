// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueSystemGameInstance.h"

//added by me
#include "ConstructorHelpers.h"
#include "DialogueManager.h"

UDialogueSystemGameInstance::UDialogueSystemGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameplayParentWidgetClassFinder(TEXT("/Game/UI/WBP_GameplayParent"));
	if (GameplayParentWidgetClassFinder.Succeeded()) {
		GameplayParentWidgetClass = GameplayParentWidgetClassFinder.Class;
	}
}

void UDialogueSystemGameInstance::Init(){
	Super::Init();

	DialogueManager = NewObject<UDialogueManager>(this);
}

void UDialogueSystemGameInstance::CreateGameUI() {

	GameplayParentWidget = CreateWidget<UUI_GameplayParent>(this, GameplayParentWidgetClass);
	if (GameplayParentWidget) {
		GameplayParentWidget->AddToViewport();
	}
}