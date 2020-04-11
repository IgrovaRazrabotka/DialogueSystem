// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueOptionSettings.h"
#include "TreeOption.generated.h"

/**
 * 
 */

USTRUCT()
struct FTreeOption
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString ID;

	UPROPERTY(EditAnywhere)
	ADialogueOptionSettings* OptionSettings;
};
