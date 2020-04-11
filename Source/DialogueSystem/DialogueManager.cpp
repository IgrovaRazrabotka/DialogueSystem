// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueManager.h"
#include "Engine.h"
#include "DialogueSystemGameInstance.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UDialogueManager::PostInitProperties() {

	Super::PostInitProperties();

	if (GetOuter() && GetOuter()->GetWorld()) BeginPlay();

}

void UDialogueManager::BeginPlay() {

	GI = Cast<UDialogueSystemGameInstance>(UGameplayStatics::GetGameInstance(this));
}

void UDialogueManager::ChangeCamera(int CameraIndex) {
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	switch (CameraIndex) {
	case 0:
		PlayerCharacter->GetFollowCamera()->SetActive(true);
		PlayerCharacter->GetDialogueCamera1()->SetActive(false);
		PlayerCharacter->GetDialogueCamera2()->SetActive(false);
		PlayerCharacter->GetDialogueCamera3()->SetActive(false);
		break;
	case 1:
		PlayerCharacter->GetFollowCamera()->SetActive(false);
		PlayerCharacter->GetDialogueCamera1()->SetActive(true);
		PlayerCharacter->GetDialogueCamera2()->SetActive(false);
		PlayerCharacter->GetDialogueCamera3()->SetActive(false);
		break;
	case 2:
		PlayerCharacter->GetFollowCamera()->SetActive(false);
		PlayerCharacter->GetDialogueCamera1()->SetActive(false);
		PlayerCharacter->GetDialogueCamera2()->SetActive(true);
		PlayerCharacter->GetDialogueCamera3()->SetActive(false);
		break;
	case 3:
		PlayerCharacter->GetFollowCamera()->SetActive(false);
		PlayerCharacter->GetDialogueCamera1()->SetActive(false);
		PlayerCharacter->GetDialogueCamera2()->SetActive(false);
		PlayerCharacter->GetDialogueCamera3()->SetActive(true);
		break;
	default:
		PlayerCharacter->GetFollowCamera()->SetActive(true);
		PlayerCharacter->GetDialogueCamera1()->SetActive(false);
		PlayerCharacter->GetDialogueCamera2()->SetActive(false);
		PlayerCharacter->GetDialogueCamera3()->SetActive(false);
	}
}

void UDialogueManager::ZeroAndLockCameraRotationInput() {

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (APlayerController* const PC = Cast<APlayerController>(PlayerCharacter->Controller)) {

		FRotator Rot = PC->GetControlRotation();
		Rot.Roll = 0;
		Rot.Pitch = 0;
		PC->SetControlRotation(Rot);
		SetLockMouseRotationInput(true);
	}
}

void UDialogueManager::SetLockMouseRotationInput(bool NewFlag) {
	bLockMouseRotationInput = NewFlag;
}

bool UDialogueManager::IsMouseRotationLocked() {
	return bLockMouseRotationInput;
}

void UDialogueManager::SetDialogueState(EDialogueState NewState) {
	if (NewState == EDialogueState::EOn) {
		GI->GameplayParentWidget->OpenDialogueWindow();
		ChangeCamera(FMath::FRandRange(1, 4));
		ZeroAndLockCameraRotationInput();
		CurrentDialogueState = EDialogueState::EOn;
	}
	else if (NewState == EDialogueState::EInProgress) {
		GI->GameplayParentWidget->CloseDialogueWindow();
		CurrentDialogueState = EDialogueState::EInProgress;
	}
	else if (NewState == EDialogueState::EOff)
	{
		ChangeCamera(0);
		SetLockMouseRotationInput(false);
		CurrentDialogueState = EDialogueState::EOff;
	}
}

EDialogueState UDialogueManager::GetDialogueState() {
	return CurrentDialogueState;
}

void UDialogueManager::StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot)
{
	GI->GameplayParentWidget->UpdateDialogueOptionsScrollBox(&dialogueTree, dialogueRoot);
	GI->GameplayParentWidget->OpenDialogueWindow();

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))) {
		RotateActorATowardsActorB(*PlayerCharacter, *dialogueTree.GetOwner());
		RotateActorATowardsActorB(*dialogueTree.GetOwner(), *PlayerCharacter);
	}

	SetDialogueState(EDialogueState::EOn);// important that this line is after StartDialogue
}

//This is useful for when the AI wants to start a conversation with the player
void UDialogueManager::StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot, FString optionID)
{
	GI->GameplayParentWidget->UpdateDialogueOptionsScrollBox(&dialogueTree, dialogueRoot);
	GI->GameplayParentWidget->OpenDialogueWindow();

	dialogueTree.SelectOptionWithID(optionID);
	SetDialogueState(EDialogueState::EInProgress);// important that this line is after StartDialogue
}

//This is useful for when the AI wants to start a conversation with the player
void UDialogueManager::StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot, ADialogueOptionSettings& option)
{
	GI->GameplayParentWidget->UpdateDialogueOptionsScrollBox(&dialogueTree, dialogueRoot);
	GI->GameplayParentWidget->OpenDialogueWindow();

	dialogueTree.SelectOption(option);
	SetDialogueState(EDialogueState::EInProgress);// important that this line is after StartDialogue
}

void UDialogueManager::RotateActorATowardsActorB(AActor& ActorA, AActor& ActorB) {
	
		FVector ToVector = ActorB.GetActorLocation() - ActorA.GetActorLocation();
		ToVector.Z = 0;
		FVector FromVector = ActorA.GetActorForwardVector();
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FromVector, ToVector);
		ActorA.SetActorRotation(Rotation);
}

void UDialogueManager::HighlightUp()
{
	GI->GameplayParentWidget->HighlightUp();
}

void UDialogueManager::HighlightDown()
{
	GI->GameplayParentWidget->HighlightDown();
}

void UDialogueManager::Select()
{
	if (CurrentDialogueState == EDialogueState::EOn) {
		SetDialogueState(EDialogueState::EInProgress);
		GI->GameplayParentWidget->SelectHighlightedOption();
	}
}