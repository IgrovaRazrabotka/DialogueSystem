// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueSelectionEffectBase.h"
#include "DialogueOptionSettings.h"
//added by me
#include "DialogueTree.h"
#include "UnrealMathUtility.h"
#include "Engine.h"
#include "PlayerCharacter.h"
#include "DialogueSystemGameInstance.h"
#include "DialogueManager.h"

ADialogueSelectionEffectBase::ADialogueSelectionEffectBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ADialogueSelectionEffectBase::BeginPlay() {

	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		TimerManager = &(GetWorld()->GetTimerManager());
		verifyf(TimerManager != nullptr, TEXT("Timer Manager cannot be null."));

		GI = World->GetGameInstance<UDialogueSystemGameInstance>();
		verifyf(IsValid(GI),TEXT("Could not find the game instance."));
		GameplayParentWidget = GI->GetGameplayParentWidget();
		verifyf(IsValid(GameplayParentWidget),TEXT("Could not find the Gameplay Parent Widget."));

	}

	EndPlaySoundCueTimerDelegate.BindUObject(this, &ADialogueSelectionEffectBase::EndPlaySoundCue);
}

void ADialogueSelectionEffectBase::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void ADialogueSelectionEffectBase::Execute()
{
	verifyf(IsValid(ParentDialogueOptionSettings), TEXT("A Dialogue Selection Effect must have a parent. \
	To have one its Parent Option must be added to an existing Dialogue Tree. Maybe you forgot to do that?"));

	AttemptPlaySoundCue();
}

void ADialogueSelectionEffectBase::AttemptPlaySoundCue() {

	PerformCustomAction();

	if (!Subtitle.IsEmpty()) {
		GameplayParentWidget->UpdateSubtitleWindowSubtitleText(Subtitle);
		GameplayParentWidget->OpenSubtitleWindow();
	}

	if (IsValid(SoundCue)) {

		verifyf(TimerManager != nullptr, TEXT("Timer Manager cannot be null."));
		float duration = SoundCue->GetDuration();
		duration = FMath::Max<float>(0.001f, duration);
		
		FVector playLocation = EffectBelongsToPlayer ? UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation() :
			ParentDialogueTree->GetOwner()->GetActorLocation();

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, playLocation);
		TimerManager->SetTimer(EndPlaySoundCueTimerHandle, EndPlaySoundCueTimerDelegate, duration, false);
	}
	else {
		EndPlaySoundCue();
	}
}

void ADialogueSelectionEffectBase::PerformCustomAction() {

	//override and implement in a derived class
}

void ADialogueSelectionEffectBase::EndPlaySoundCue() {

	GameplayParentWidget->CloseSubtitleWindow();
	AttemptPlayOption();
}


void ADialogueSelectionEffectBase::AttemptPlayOption() {

	
	if (DoPlayOption) {

		verifyf(IsValid(OptionToPlay), TEXT("You requested to play an option on other character but you did not provide a valid reference to an option."));

		OptionToPlay->ParentEffect = this;
		ParentDialogueTree->SelectOption(*OptionToPlay);
	} 
	else {
		AttemptDoBranch();
	}
}

void ADialogueSelectionEffectBase::OnPlayOptionCompleted() {
	
	AttemptDoBranch();
}

void ADialogueSelectionEffectBase::AttemptDoBranch() {
	
	if (DoBranch) {
		GameplayParentWidget->UpdateDialogueOptionsScrollBox(ParentDialogueTree, BranchID);
	}

	AttemptEndDialogue();
}
void ADialogueSelectionEffectBase::AttemptEndDialogue() {
	
	if (DoEndDialogue) {
		GameplayParentWidget->CloseSubtitleWindow();
		GameplayParentWidget->CloseDialogueWindow();
		GI->DialogueManager->SetDialogueState(EDialogueState::EOff);
		//Note that this will interrupt any chain of effects' execution - END means END - further effects are not executed even if available
	}
	else {
		CompleteExecution();
	}
}

void ADialogueSelectionEffectBase::CompleteExecution() {

	ParentDialogueOptionSettings->OnEffectExecutionCompleted();
}