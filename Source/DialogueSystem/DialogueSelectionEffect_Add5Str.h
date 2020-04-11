// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueSelectionEffectBase.h"
#include "DialogueSelectionEffect_Add5Str.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API ADialogueSelectionEffect_Add5Str : public ADialogueSelectionEffectBase
{
	GENERATED_BODY()
protected:
		virtual void PerformCustomAction() override;
};
