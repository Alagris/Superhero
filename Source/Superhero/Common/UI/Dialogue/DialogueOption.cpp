// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/Dialogue/DialogueOption.h"
#include <Components/ListViewBase.h>
#include <Common/UI/Dialogue/DialogueResponseListView.h>
#include "DialogueResponse.h"


void UDialogueOption::NativeConstruct()
{
	Super::NativeConstruct();
	OptionButton->OnClicked.AddUniqueDynamic(this, &UDialogueOption::OnOptionClick);
}

void UDialogueOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UListViewBase* owner = GetOwningListView();
	Parent = Cast<UDialogueResponseListView>(owner);
	check(Parent != nullptr);
	DialogueResponse = Cast<UDialogueResponse>(ListItemObject);
	TextOption->SetText(FText::FromString(DialogueResponse->PlayerText));
}

void UDialogueOption::OnOptionClick()
{
	Parent->chooseOption(DialogueResponse);

}
