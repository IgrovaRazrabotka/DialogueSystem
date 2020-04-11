// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_DialogueOptionEntry.h"
#include "WidgetTree.h"
#include "TextBlock.h"

void UUI_DialogueOptionEntry::Init(FTreeOption UniqueOption)
{
	ID = UniqueOption.ID;
	SetText(UniqueOption.OptionSettings->Text);
}

void UUI_DialogueOptionEntry::SetText(FString NewText)
{
	verifyf(WidgetTree != nullptr, TEXT("Error: WidgetTree cannot be null."));
	UTextBlock* TextBlock = WidgetTree->FindWidget<UTextBlock>(TEXT("DialogueOptionText"));
	verifyf(TextBlock != nullptr, TEXT("Error: TextBlock cannot be null."));
	TextBlock->SetText(FText::FromString(NewText));
}

