// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DialogueSystemGameMode.generated.h"

UCLASS(minimalapi)
class ADialogueSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADialogueSystemGameMode();

	void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage);
};



