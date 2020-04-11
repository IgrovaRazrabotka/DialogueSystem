// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueTree.h"
#include "DialogueManager.generated.h"

/**
 * 
 */

enum class EDialogueState {
	EOn = 0,
	EInProgress,
	EOff
};

UCLASS()
class DIALOGUESYSTEM_API UDialogueManager : public UObject
{
	GENERATED_BODY()
	
	virtual void PostInitProperties() override;
	void BeginPlay();

protected:
	
	void ChangeCamera(int CameraIndex);
	void ZeroAndLockCameraRotationInput();
	void SetLockMouseRotationInput(bool NewFlag);
	bool IsMouseRotationLocked();

	bool bLockMouseRotationInput = false;
	EDialogueState CurrentDialogueState = EDialogueState::EOff;
	class UDialogueSystemGameInstance* GI = nullptr;
	//class APlayerCharacter* PlayerCharacter = nullptr;

public:
	void SetDialogueState(EDialogueState NewState);
	EDialogueState GetDialogueState();
	void StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot);
	void StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot, FString optionID);
	void StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot, ADialogueOptionSettings& option);
	void RotateActorATowardsActorB(AActor& ActorA, AActor& ActorB);
	void HighlightUp();
	void HighlightDown();
	void Select();
};
