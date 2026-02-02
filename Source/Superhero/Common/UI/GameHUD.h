// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Dialogue/Dialogue.h"
#include "PauseMenu/PauseMenu.h"
#include "GameHUD.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API AGameHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UDialogue> DialogueWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UPauseMenu> PauseMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UDialogue> DialogueWidget;

	UPROPERTY()
	TObjectPtr<UPauseMenu> PauseMenuWidget;

public:
	bool showDialogue(APlayerController* PlayerController, TScriptInterface<IDialogueActor> Npc, TSoftObjectPtr<UDialogueStage> Stage);

	void triggerPauseGame(APlayerController* PlayerController);

	bool hideDialogue(APlayerController* PlayerController);

	bool showPauseMenu(APlayerController* controller);

	bool hidePauseMenu(APlayerController* PlayerController);
	
	inline bool canOpenPauseMenu() {
		return IsValid(PauseMenuWidgetClass);
	}

	inline bool canOpenDialogue() {
		return IsValid(DialogueWidgetClass);
	}

	inline bool isPauseMenuOpen() {
		return IsValid(PauseMenuWidget);
	}

	inline bool isDialogueOpen() {
		return IsValid(DialogueWidget);
	}
};
