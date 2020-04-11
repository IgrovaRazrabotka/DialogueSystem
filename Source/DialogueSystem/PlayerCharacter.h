// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

UCLASS()
class DIALOGUESYSTEM_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* DialogueCameraBoom1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* DialogueCameraBoom2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* DialogueCameraBoom3;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* DialogueCamera1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* DialogueCamera2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* DialogueCamera3;

	UPROPERTY(EditAnywhere)
		USphereComponent* PlayerRangeCollision;
	UPROPERTY(EditAnywhere)
		AActor* CurrentIdentityActor = nullptr;

	UPROPERTY(EditAnywhere)
		float InteractionDistance = 500.0f;

	//UPROPERTY()
		//AActor* CurrentDialogueCharacter = nullptr;

public:
	//void SetDialogueState(EDialogueState NewState);
	//EDialogueState GetDialogueState();

protected:
	//--
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsInIdentityDetectionCone(AActor* ActorToCheck);
	void SortActorsByDescDistanceToPlayer(TArray<AActor*>& Actors, AActor* Player);
	void DetectIdentityActorsInScene();
	
	UFUNCTION()
	void OnIdentityEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnIdentityExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	TArray<AActor*> CurrentlyShowingIdentities;

	//void ChangeCamera(int CameraIndex);
	//void ZeroAndLockCameraRotationInput();
	//void SetLockMouseRotationInput(bool NewFlag);
	//bool IsMouseRotationLocked();

	void Interact();
	//void StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot);
	//void StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot, FString optionID);
	//void StartDialogue(UDialogueTree& dialogueTree, FString dialogueRoot, ADialogueOptionSettings& option);
	//void HighlightUp();
	//void HighlightDown();
	//void Select();

	virtual void MoveForward(float Value) override;
	/** Called for side to side input */
	virtual void MoveRight(float Value) override;

	void HighlightUp();
	void HighlightDown();

	void TurnCamera(float Val);
	void LookUpCamera(float Val);

	//--
	//bool bLockMouseRotationInput = false;
	//EDialogueState CurrentDialogueState = EDialogueState::ENotInProgress;
public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		UDialogueSystemGameInstance* GameInstance = nullptr;

	UPROPERTY()
		UUI_GameplayParent* GameplayParentWidget = nullptr;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetDialogueCameraBoom1() const { return DialogueCameraBoom1; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetDialogueCamera1() const { return DialogueCamera1; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetDialogueCameraBoom2() const { return DialogueCameraBoom2; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetDialogueCamera2() const { return DialogueCamera2; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetDialogueCameraBoom3() const { return DialogueCameraBoom3; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetDialogueCamera3() const { return DialogueCamera3; }
};
