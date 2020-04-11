// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

//added by me
#include "UI_GameplayParent.h"
//
#include "DialogueSystemGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UDialogueSystemGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDialogueSystemGameInstance();

	virtual void Init() override;

	void CreateGameUI();

	
	UUI_GameplayParent* GetGameplayParentWidget()
	{
		return GameplayParentWidget;
	};

protected:

	UPROPERTY()
	UClass* GameplayParentWidgetClass;

public:
	UPROPERTY()
	UUI_GameplayParent* GameplayParentWidget;

	UPROPERTY()
	class UDialogueManager* DialogueManager = nullptr;
};
