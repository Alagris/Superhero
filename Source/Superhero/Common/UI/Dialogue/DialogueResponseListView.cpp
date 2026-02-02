// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/Dialogue/DialogueResponseListView.h"
#include "DialogueStage.h"
#include "Dialogue.h"
#include "DialogueResponse.h"


void UDialogueResponseListView::chooseOption(TObjectPtr<UDialogueResponse> resp)
{
	
	resp->OnChosen();
	Root->followUp(resp->Next);
}
