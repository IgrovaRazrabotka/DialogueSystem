// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueOptionSettings.h"
#include "DialogueSelectionEffectBase.h"
#include "Engine.h"
#include "DialogueSystemGameInstance.h"
#include "DialogueManager.h"

// Sets default values
ADialogueOptionSettings::ADialogueOptionSettings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADialogueOptionSettings::BeginPlay()
{
	Super::BeginPlay();

	GI = GetGameInstance<UDialogueSystemGameInstance>();
}

void ADialogueOptionSettings::Init(UDialogueTree* dialogueTree) {

	verifyf(dialogueTree != nullptr, TEXT("A dialogue option and its children effects cannot be \
		 initialized with a NULL dialogue tree."));
	for (int i = 0; i < Effects.Num(); i++) {
		if (IsValid(Effects[i])) {
			Effects[i]->ParentDialogueOptionSettings = this;
			Effects[i]->ParentDialogueTree = dialogueTree;
		}
	}
}

void ADialogueOptionSettings::Execute() {

	if (Effects.Num() > 0) {
		NextEffectToExecute = 0;
		ExecuteNextEffect();
	}
}

void ADialogueOptionSettings::ExecuteNextEffect() {
	
	ADialogueSelectionEffectBase* NextEffect = nullptr;

	if (Effects.Num() > 0) {
		if (Effects.IsValidIndex(NextEffectToExecute)) {

			verifyf(IsValid(Effects[NextEffectToExecute]), TEXT("Error: An effect is null. Did you forget to add one?"))
			NextEffect = Effects[NextEffectToExecute];
			NextEffect->Execute();
		}
		else {
			OnOptionExecutionCompleted();
		}
	}
}

// this is called be each effect after it ends its execution - this design is used for delays
void ADialogueOptionSettings::OnEffectExecutionCompleted() {

	RequestExecuteNextEffect();
}

void ADialogueOptionSettings::RequestExecuteNextEffect() {

	NextEffectToExecute++;
	ExecuteNextEffect();
}

void ADialogueOptionSettings::OnOptionExecutionCompleted() {

	if (IsValid(ParentEffect)) {
		ParentEffect->OnPlayOptionCompleted();
	}
	else {// in caes the option execution is absolutely complete and has no parent which invoked it
		GI->DialogueManager->SetDialogueState(EDialogueState::EOn);
	}
}

// Called every frame
void ADialogueOptionSettings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

