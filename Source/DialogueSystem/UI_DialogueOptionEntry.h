// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//added by me
#include "DialogueOptionSettings.h"
#include "TreeOption.h"
#include "UI_DialogueOptionEntry.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UUI_DialogueOptionEntry : public UUserWidget
{
	GENERATED_BODY()
	

public:

	FString ID;

	void Init(FTreeOption UniqueOption);
	
	void SetText(FString NewText);
};
