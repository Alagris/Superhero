// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/UI/IndexedListView.h"
#include "DialogueResponseListView.generated.h"

class UDialogue;
class UDialogueStage;
class IDialogueActor;
class UDialogueResponse;
/**
 * 
 */
UCLASS()
class SUPERHERO_API UDialogueResponseListView : public UListView
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDialogue* Root;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	TScriptInterface<IDialogueActor> Npc;

	UPROPERTY()
	TObjectPtr<UDialogueStage> DialogueStage;

	void chooseOption(TObjectPtr<UDialogueResponse> resp);
};
