// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueTree.h"

// Sets default values for this component's properties
UDialogueTree::UDialogueTree()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueTree::BeginPlay()
{
	Super::BeginPlay();

	for (auto Iter = Options.CreateIterator(); Iter; ++Iter)
	{
		Iter->OptionSettings->Init(this);
	}
	
}


// Called every frame
void UDialogueTree::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UDialogueTree::HasBranchWithID(FString RootID)
{
	if (Options.Num() > 0) {
		for (auto Iter = Options.CreateIterator(); Iter; ++Iter)
		{
			if (Iter->OptionSettings->Root == RootID) return true;
		}
	}
	return false;
}

TArray<FTreeOption> UDialogueTree::GetBranchOptions(FString RootID) //get the active / available root options of a tree (like homepage of a website)
{
	TArray<FTreeOption> BranchOptions;
	for (auto Iter = Options.CreateIterator(); Iter; ++Iter)
	{
		if (Iter->OptionSettings->Root == RootID) BranchOptions.Add(*Iter);
	}
	return BranchOptions;
}

void UDialogueTree::SelectOptionWithID(FString ID)
{
	for (auto Iter = Options.CreateIterator(); Iter; ++Iter) {
		if ((*Iter).ID == ID) {
			(*Iter).OptionSettings->Execute();
			break;
		}
	}
}

void UDialogueTree::SelectOption(ADialogueOptionSettings& Option)
{
		Option.Execute();
}

