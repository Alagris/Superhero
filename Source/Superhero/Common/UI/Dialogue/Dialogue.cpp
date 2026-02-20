// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/Dialogue/Dialogue.h"
#include "DialogueStage.h"
#include "DialogueResponse.h"
#include "DialogueActor.h"
#include "DialogueResponseListView.h"
#include <Common/UI/GameHUD.h>

void UDialogue::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
	SetVisibility(ESlateVisibility::Collapsed);
}

FReply UDialogue::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Escape) {
		closeDialogue();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UDialogue::setup(AGameHUD* hud, APlayerController* PlayerController, TScriptInterface<IDialogueActor> Npc, TSoftObjectPtr<UDialogueStage> Stage)
{
	this->HUD = hud;
	ResponseOptions->Root = this;
	ResponseOptions->Npc = Npc;
	ResponseOptions->PlayerController = PlayerController;
	IDialogueActor::Execute_OnDialogueEntered(Npc.GetObject(), PlayerController);
	//Npc->OnEnterDialogue(player);
	SetVisibility(ESlateVisibility::Visible);
	FText NpcName = IDialogueActor::Execute_GetCharacterName(Npc.GetObject());
	SpeakerName->SetText(NpcName);
	followUp(Stage);
}

void UDialogue::closeDialogue()
{
	
	IDialogueActor::Execute_OnDialogueExited(ResponseOptions->Npc.GetObject(), ResponseOptions->PlayerController);
	HUD->hideDialogue();
}

void UDialogue::followUp(TSoftObjectPtr<UDialogueStage> Stage)
{
	if (Stage.IsNull()) {
		closeDialogue();
	}
	else {
		UDialogueStage * s = Stage.LoadSynchronous();
		SpeakerText->SetText(s->NpcText);
		if (IsValid(s->Animation)) {
			IDialogueActor::Execute_OnPlayDialogueAnim(ResponseOptions->Npc.GetObject(), s->Animation);
		}
		clearOptions();
		for (int i = 0; i < s->Responses.Num(); i++) {
			if (IsValid(s->Responses[i])) {
				TObjectPtr<UDialogueResponse> resp = s->Responses[i];
				if (resp->CheckCondition()) {
					ResponseOptions->AddItem(resp);
				}
			}
		}
	}
}
