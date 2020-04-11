// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_GameplayParent.h"

//included by me
#include "ConstructorHelpers.h"
#include "WidgetTree.h"
//

UUI_GameplayParent::UUI_GameplayParent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> DialogueOptionEntryClassFinder(TEXT("/Game/UI/WBP_DialogueOptionEntry"));
	verifyf(DialogueOptionEntryClassFinder.Class != nullptr, TEXT("Error: could not find /Game/UI/WBP_DialogueOptionEntry."));
	DialogueOptionEntryClass = DialogueOptionEntryClassFinder.Class;
}

void UUI_GameplayParent::UpdateDialogueOptionsScrollBox(UDialogueTree* DialogueTree, FString BranchID)
{
	verifyf(DialogueTree != nullptr, TEXT("Error: DialogueTree is null."));
	verifyf(DialogueOptionEntryClass != nullptr, TEXT("Error: DialogueOptionEntryClass is null."));
	verifyf(DialogueTree->HasBranchWithID(BranchID), TEXT("Error: Could not find specified branch. Are you sure a branch with that ID exists?"));

	CurrentTree = DialogueTree;

	TArray<FTreeOption> Options = CurrentTree->GetBranchOptions(BranchID);
	DialogueOptionsScrollBox->ClearChildren();
	preservationArray.Empty();
	for (auto Iter = Options.CreateIterator(); Iter; ++Iter)
	{
		UUI_DialogueOptionEntry* DO = CreateWidget<UUI_DialogueOptionEntry>(this, DialogueOptionEntryClass);
		preservationArray.Add(DO);
		if (DO)
		{
			DO->Init((*Iter));
			DialogueOptionsScrollBox->AddChild(DO);
		}
	}

	HighlightDefault();
}

void UUI_GameplayParent::HighlightDefault()
{
	if (DialogueOptionsScrollBox->GetChildrenCount() > 0)
	{
		if (UUI_DialogueOptionEntry* OptionEntry = Cast<UUI_DialogueOptionEntry>(DialogueOptionsScrollBox->GetChildAt(0)))
		{
			if (UTextBlock* TextBlock = OptionEntry->WidgetTree->FindWidget<UTextBlock>(TEXT("DialogueOptionText")))
			{
				FSlateFontInfo FontInfo = TextBlock->Font;
				FontInfo.TypefaceFontName = FName(TEXT("Bold"));
				TextBlock->SetFont(FontInfo);
				HighlightedOption = 0;
			}
		}
	}
}

void UUI_GameplayParent::HighlightUp()
{
	if (HighlightedOption > 0 && HighlightedOption < DialogueOptionsScrollBox->GetChildrenCount())
	{
		if (UUI_DialogueOptionEntry* UpperOptionEntry = Cast<UUI_DialogueOptionEntry>(DialogueOptionsScrollBox->GetChildAt(HighlightedOption - 1)))
		{
			if (UTextBlock* UpperTextBlock = UpperOptionEntry->WidgetTree->FindWidget<UTextBlock>(TEXT("DialogueOptionText")))
			{
				if (UUI_DialogueOptionEntry* OldOptionEntry = Cast<UUI_DialogueOptionEntry>(DialogueOptionsScrollBox->GetChildAt(HighlightedOption)))
				{
					if (UTextBlock* OldTextBlock = OldOptionEntry->WidgetTree->FindWidget<UTextBlock>(TEXT("DialogueOptionText")))
					{
						FSlateFontInfo BoldFontInfo = OldTextBlock->Font;
						FSlateFontInfo LightFontInfo = UpperTextBlock->Font;

						UpperTextBlock->SetFont(BoldFontInfo);
						OldTextBlock->SetFont(LightFontInfo);
						HighlightedOption--;
					}
				}
			}
		}
	}
}

void UUI_GameplayParent::HighlightDown()
{
	if (HighlightedOption >= 0 && HighlightedOption < DialogueOptionsScrollBox->GetChildrenCount() - 1)
	{
		if (UUI_DialogueOptionEntry* LowerOptionEntry = Cast<UUI_DialogueOptionEntry>(DialogueOptionsScrollBox->GetChildAt(HighlightedOption + 1)))
		{
			if (UTextBlock* LowerTextBlock = LowerOptionEntry->WidgetTree->FindWidget<UTextBlock>(TEXT("DialogueOptionText")))
			{
				if (UUI_DialogueOptionEntry* OldOptionEntry = Cast<UUI_DialogueOptionEntry>(DialogueOptionsScrollBox->GetChildAt(HighlightedOption)))
				{
					if (UTextBlock* OldTextBlock = OldOptionEntry->WidgetTree->FindWidget<UTextBlock>(TEXT("DialogueOptionText")))
					{
						FSlateFontInfo BoldFontInfo = OldTextBlock->Font;
						FSlateFontInfo LightFontInfo = LowerTextBlock->Font;

						LowerTextBlock->SetFont(BoldFontInfo);
						OldTextBlock->SetFont(LightFontInfo);
						HighlightedOption++;
					}
				}
			}
		}
	}
}

void UUI_GameplayParent::CloseDialogueWindow()
{
	DialogueOptionsBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_GameplayParent::OpenDialogueWindow()
{
	DialogueOptionsBorder->SetVisibility(ESlateVisibility::Visible);
}

void UUI_GameplayParent::SelectHighlightedOption()
{
	if (HighlightedOption >= 0 && HighlightedOption < DialogueOptionsScrollBox->GetChildrenCount())
	{
		if (CurrentTree)
		{
			UUI_DialogueOptionEntry* HighlightedEntry = Cast<UUI_DialogueOptionEntry>(DialogueOptionsScrollBox->GetChildAt(HighlightedOption));
			CurrentTree->SelectOptionWithID(HighlightedEntry->ID);
		}
	}
}

// SUBTITLE WINDOW ========================

void UUI_GameplayParent::OpenSubtitleWindow() {

	SubtitleBorder->SetVisibility(ESlateVisibility::Visible);
}

void UUI_GameplayParent::UpdateSubtitleWindowSubtitleText(FString Text) {

	SubtitleText->SetText(FText::FromString(Text));
}

void UUI_GameplayParent::CloseSubtitleWindow() {

	SubtitleBorder->SetVisibility(ESlateVisibility::Hidden);
}