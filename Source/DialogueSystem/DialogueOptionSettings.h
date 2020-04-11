// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "DialogueOptionSettings.generated.h"

UCLASS()
class DIALOGUESYSTEM_API ADialogueOptionSettings : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		class UDialogueTree* ParentDialogueTree = nullptr;

	UPROPERTY(EditAnywhere)
		FString Root = "Root";

	UPROPERTY(EditAnywhere)
		FString Text = "Default Option Text";
	
	UPROPERTY(EditAnywhere)
		bool bIsVisible;

	UPROPERTY(VisibleAnywhere)
		class ADialogueSelectionEffectBase* ParentEffect = nullptr;

	UPROPERTY(EditAnywhere)
		TArray<class ADialogueSelectionEffectBase*> Effects;

	UPROPERTY()
		class UDialogueSystemGameInstance* GI = nullptr;
protected:
	UPROPERTY()
		int NextEffectToExecute = 0;

public:	
	// Sets default values for this actor's properties
	ADialogueOptionSettings();

	virtual void Init(UDialogueTree* dialogueTree);

	virtual void Execute();

	// This is called when an effect from the array finishes its execution (delays and other things included)
	virtual void OnEffectExecutionCompleted();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void RequestExecuteNextEffect();
	
	virtual void ExecuteNextEffect();

	// if this option was originally invoked by some effect -> report back to that effect that the option is completed
	virtual void OnOptionExecutionCompleted();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
