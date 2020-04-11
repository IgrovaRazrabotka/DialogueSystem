// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "NonPlayerCharacter.h"
#include "IdentityAComp.h"
#include "DialogueManager.h"

APlayerCharacter::APlayerCharacter() {
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	DialogueCameraBoom1 = CreateDefaultSubobject<USpringArmComponent>(TEXT("DialogueCameraBoom1"));
	DialogueCameraBoom1->SetupAttachment(RootComponent);
	DialogueCameraBoom1->TargetArmLength = 200.0f;
	DialogueCameraBoom1->bUsePawnControlRotation = true;

	DialogueCameraBoom2 = CreateDefaultSubobject<USpringArmComponent>(TEXT("DialogueCameraBoom2"));
	DialogueCameraBoom2->SetupAttachment(RootComponent);
	DialogueCameraBoom2->TargetArmLength = 200.0f;
	DialogueCameraBoom2->bUsePawnControlRotation = true;

	DialogueCameraBoom3 = CreateDefaultSubobject<USpringArmComponent>(TEXT("DialogueCameraBoom3"));
	DialogueCameraBoom3->SetupAttachment(RootComponent);
	DialogueCameraBoom3->TargetArmLength = 200.0f;
	DialogueCameraBoom3->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	DialogueCamera1 = CreateDefaultSubobject<UCameraComponent>(TEXT("DialogueCamera1"));
	DialogueCamera1->SetupAttachment(DialogueCameraBoom1, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	DialogueCamera1->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	DialogueCamera2 = CreateDefaultSubobject<UCameraComponent>(TEXT("DialogueCamera2"));
	DialogueCamera2->SetupAttachment(DialogueCameraBoom2, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	DialogueCamera2->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	DialogueCamera3 = CreateDefaultSubobject<UCameraComponent>(TEXT("DialogueCamera3"));
	DialogueCamera3->SetupAttachment(DialogueCameraBoom3, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	DialogueCamera3->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PlayerRangeCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Player Range"));
	PlayerRangeCollision->SetupAttachment(RootComponent);
	PlayerRangeCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	PlayerRangeCollision->bHiddenInGame = false;
	PlayerRangeCollision->InitSphereRadius(1.0f);
}

void APlayerCharacter::BeginPlay() {

	Super::BeginPlay();

	GameInstance = GetGameInstance<UDialogueSystemGameInstance>();
	verifyf(GameInstance != nullptr, TEXT("Failed to get game instance."));
	GameplayParentWidget = GameInstance->GetGameplayParentWidget();
	verifyf(GameplayParentWidget != nullptr, TEXT("Failed to get parent gameplay UI widget."));
	PlayerRangeCollision->OnComponentBeginOverlap.AddDynamic(this,&APlayerCharacter::OnIdentityEnter);
	PlayerRangeCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnIdentityExit);
	PlayerRangeCollision->SetSphereRadius(500.0f,true);//set here to refresh if tehre is the edge case where things overlap initially.
}

bool APlayerCharacter::IsInIdentityDetectionCone(AActor* ActorToCheck) {

	if (ActorToCheck) {

		FVector Position = ActorToCheck->GetActorLocation();

		FVector VectorTowardClosestTarget = Position - GetActorLocation();
		VectorTowardClosestTarget.Normalize();

		FRotator Rot = GetControlRotation();
		FVector CameraForward = Rot.Vector();
		CameraForward.Normalize();

		float Result = FVector::DotProduct(VectorTowardClosestTarget, CameraForward);

		if (Result > 0.9f) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void APlayerCharacter::SortActorsByDescDistanceToPlayer(TArray<AActor*>& Actors, AActor* Player) {
	if (Player) {
		Actors.Sort([Player](const AActor& a1, const AActor& a2) {
			float size1 = FMath::Abs((a1.GetActorLocation() - Player->GetActorLocation()).Size());
			float size2 = FMath::Abs((a2.GetActorLocation() - Player->GetActorLocation()).Size());
			return  size1 < size2;
		});
	}
}

void APlayerCharacter::OnIdentityEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) {
		if (UIdentityAComp* IdentityComp = Cast<UIdentityAComp>(OtherActor->GetComponentByClass(UIdentityAComp::StaticClass()))) {
			if (!CurrentlyShowingIdentities.Contains(OtherActor)) {
				CurrentlyShowingIdentities.Add(OtherActor);
			}
		}
	}
}

void APlayerCharacter::OnIdentityExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor) {
		if (UIdentityAComp* IdentityComp = Cast<UIdentityAComp>(OtherActor->GetComponentByClass(UIdentityAComp::StaticClass()))) {
			CurrentlyShowingIdentities.Remove(OtherActor);
			IdentityComp->Hide();
		}
	}
}

void APlayerCharacter::DetectIdentityActorsInScene() {
	SortActorsByDescDistanceToPlayer(CurrentlyShowingIdentities, this);

	TArray<UIdentityAComp*> DrawCandidates;
	for (auto Iter = CurrentlyShowingIdentities.CreateIterator(); Iter; ++Iter) {
		if (UIdentityAComp* IdentityComp = Cast<UIdentityAComp>((*Iter)->GetComponentByClass(UIdentityAComp::StaticClass()))) {
			if (IsInIdentityDetectionCone(*Iter))
			{
				DrawCandidates.Add(IdentityComp);
			}
			else {
				IdentityComp->Hide();
			}
		}
	}

	CurrentIdentityActor = nullptr;

	for (int i = 0; i < DrawCandidates.Num(); ++i) {

		if (UIdentityAComp* ClosestCandidate = DrawCandidates[i]) {
			if (i == 0) {
				ClosestCandidate->Show();
				CurrentIdentityActor = ClosestCandidate->GetOwner();
			}
			else {
				ClosestCandidate->Hide();
			}
		}
	}
	DrawCandidates.Empty();
}

void APlayerCharacter::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	DetectIdentityActorsInScene();
}



void APlayerCharacter::TurnCamera(float Val) {
	if (GameInstance->DialogueManager->GetDialogueState() == EDialogueState::EOff) {
		AddControllerYawInput(Val);
	}
}

void APlayerCharacter::LookUpCamera(float Val) {
	if (GameInstance->DialogueManager->GetDialogueState() == EDialogueState::EOff) {
		AddControllerPitchInput(Val);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//added by me
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("HighlightUp", IE_Released, this, &APlayerCharacter::HighlightUp);
	PlayerInputComponent->BindAction("HighlightDown", IE_Released, this, &APlayerCharacter::HighlightDown);
	//PlayerInputComponent->BindAction("Select", IE_Released, this, &APlayerCharacter::Select);
	//

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::TurnCamera);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUpCamera);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &APlayerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlayerCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &APlayerCharacter::OnResetVR);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (GameInstance->DialogueManager->GetDialogueState() == EDialogueState::EOff) {

		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (GameInstance->DialogueManager->GetDialogueState() == EDialogueState::EOff) {
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayerCharacter::HighlightUp() {
	GameInstance->DialogueManager->HighlightUp();
}

void APlayerCharacter::HighlightDown() {
	GameInstance->DialogueManager->HighlightDown();
}

//added by me

void APlayerCharacter::Interact()
{
	if (GameInstance->DialogueManager->GetDialogueState() == EDialogueState::EOff) {

		if (CurrentIdentityActor) {

			if (UDialogueTree* DialogueTreeComponent = Cast<UDialogueTree>(CurrentIdentityActor->GetComponentByClass(UDialogueTree::StaticClass()))) {
				GameInstance->DialogueManager->StartDialogue(*DialogueTreeComponent, "Root");
			}
		}
	}
	else if (GameInstance->DialogueManager->GetDialogueState() == EDialogueState::EOn) {
		GameInstance->DialogueManager->Select();
	}
}



