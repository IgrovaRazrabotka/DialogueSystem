// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//included by me
#include "ScrollBox.h"
#include "WidgetSwitcher.h"
#include "VerticalBox.h"
#include "Border.h"
#include "TextBlock.h"
#include "DialogueTree.h"
#include "UI_DialogueOptionEntry.h"
#include "DialogueOptionSettings.h"
//

#include "UI_GameplayParent.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UUI_GameplayParent : public UUserWidget
{
	GENERATED_BODY()

public:

	UUI_GameplayParent(const FObjectInitializer& ObjectInitializer);
	
	// GENERAL

	UPROPERTY(Meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(Meta = (BindWidget))
	UVerticalBox* DialogueSystemVerticalBox;
	
	UPROPERTY(Meta = (BindWidget))
	UBorder* NoUIBorder;
	// DIALOGUE WINDOW =================

	UClass* DialogueOptionEntryClass;

	UPROPERTY(Meta = (BindWidget))
	UBorder* DialogueOptionsBorder;

	UPROPERTY(Meta = (BindWidget))
	UScrollBox* DialogueOptionsScrollBox;

	int HighlightedOption = -1;// since we might have nothing to display and thus highlight
	
	// SUBTITLE WINDOW ================

	UPROPERTY(Meta = (BindWidget))
	UBorder* SubtitleBorder;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* SubtitleText;

	//DIALOGUE WINDOW=================
	void UpdateDialogueOptionsScrollBox(UDialogueTree* DialogueTree, FString BranchID);

	void HighlightDefault();

	void HighlightUp();

	void HighlightDown();

	void CloseDialogueWindow();

	void OpenDialogueWindow();

	void SelectHighlightedOption();

	//SUBTITLE WINDOW ==================

	void OpenSubtitleWindow();

	void UpdateSubtitleWindowSubtitleText(FString Text);

	void CloseSubtitleWindow();

private:

	// DIALOGUE WINDOW
	UPROPERTY()
	TArray<UUI_DialogueOptionEntry*> preservationArray;

	UPROPERTY()
	UDialogueTree* CurrentTree;
	
};
