// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueSelectionEffectBase.h"
#include "DialogueOptionSettings.h"
#include "Engine.h"
#include "TreeOption.h"
#include "DialogueTree.generated.h"


UCLASS( ClassGroup=(Custom), EditInlineNew, meta=(BlueprintSpawnableComponent) )
class DIALOGUESYSTEM_API UDialogueTree : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueTree();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	


	UPROPERTY(EditAnywhere)
	TArray<FTreeOption> Options;

	UPROPERTY()
	TMap<FString, ADialogueOptionSettings*> BufferOptions;
		
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<FTreeOption> GetBranchOptions(FString RootID); //get the active / available root options of a tree (like homepage of a website)

	bool HasBranchWithID(FString RootID);

	void SelectOptionWithID(FString ID);
	void SelectOption(ADialogueOptionSettings& Option);
		
};
