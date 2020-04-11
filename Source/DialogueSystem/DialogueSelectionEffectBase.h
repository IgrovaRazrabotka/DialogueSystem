// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"
#include "DialogueOptionSettings.h"
#include "DialogueSelectionEffectBase.generated.h"

UCLASS()
class DIALOGUESYSTEM_API ADialogueSelectionEffectBase : public AActor
{
	GENERATED_BODY()

public:

	virtual void Execute();


	UPROPERTY()
		class UDialogueTree* ParentDialogueTree;

	UPROPERTY()
		ADialogueOptionSettings* ParentDialogueOptionSettings;
	
	UPROPERTY(EditAnywhere)
		//True when bolonging to player / False when belonging to non-player
		bool EffectBelongsToPlayer = true;

	UPROPERTY(EditAnywhere)
		USoundCue* SoundCue = nullptr;

	UPROPERTY(EditAnywhere)
		FString Subtitle = "Default Option Subtitle";

	UPROPERTY(EditAnywhere)
		bool DoPlayOption = false;
	UPROPERTY(EditAnywhere)
		ADialogueOptionSettings* OptionToPlay = nullptr;
	
	UPROPERTY(EditAnywhere)
		bool DoBranch = false;
	UPROPERTY(EditAnywhere)
		FString BranchID;
	
	UPROPERTY(EditAnywhere)
		bool DoEndDialogue = false;

protected:

	UPROPERTY()
	class UUI_GameplayParent* GameplayParentWidget;

	FTimerManager* TimerManager;
	FTimerHandle EndPlaySoundCueTimerHandle;
	FTimerDelegate EndPlaySoundCueTimerDelegate;

	UPROPERTY()
	class UDialogueSystemGameInstance* GI = nullptr;

public:
	ADialogueSelectionEffectBase();

	virtual void OnPlayOptionCompleted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AttemptPlaySoundCue();
	virtual void PerformCustomAction();
	virtual void EndPlaySoundCue();
	virtual void AttemptPlayOption();
	virtual void AttemptDoBranch();
	virtual void AttemptEndDialogue();
	virtual void CompleteExecution();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
