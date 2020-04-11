// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IdentityAComp.generated.h"

class UWidgetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGUESYSTEM_API UIdentityAComp : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIdentityAComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY()
	UWidgetComponent* Widget = nullptr;
	UPROPERTY()
	UClass* WidgetClass = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Show();
	virtual void Hide();
		
};
