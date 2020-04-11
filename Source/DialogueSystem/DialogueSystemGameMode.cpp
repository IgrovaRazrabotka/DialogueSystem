// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DialogueSystemGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

//included by me
#include "DialogueSystemGameInstance.h"
//

ADialogueSystemGameMode::ADialogueSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADialogueSystemGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) {

	UWorld* world = GetWorld();
	if (world) {
		UDialogueSystemGameInstance* mgi = world->GetGameInstance<UDialogueSystemGameInstance>();
		if (mgi) {
			mgi->CreateGameUI();
		}
	}

	Super::InitGame(MapName, Options, ErrorMessage);
}
