// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueSelectionEffect_Add5Str.h"
#include "Engine.h"

void ADialogueSelectionEffect_Add5Str::PerformCustomAction() {

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Improved strength by 5."));
	}

}