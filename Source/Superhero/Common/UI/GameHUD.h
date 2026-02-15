// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Dialogue/Dialogue.h"
#include "PauseMenu/PauseMenu.h"
#include "CharacterMenu/CharacterMenu.h"
#include "Inventory/InventoryMenu.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UCharacterMenu> CharacterMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UInventoryMenu> InventoryMenuClass;

	UPROPERTY()
	TObjectPtr<UDialogue> DialogueWidget;

	UPROPERTY()
	TObjectPtr<UPauseMenu> PauseMenuWidget;

	UPROPERTY()
	TObjectPtr<UCharacterMenu> CharacterMenuWidget;

	UPROPERTY()
	TObjectPtr<UInventoryMenu> InventoryMenuWidget;

public:
	bool showInventoryMenu(APlayerController* PlayerController, class UInventory* Inv);

	bool showCharacterMenu(APlayerController* PlayerController, class AIndoorsSuperhero * Hero);

	bool showDialogue(APlayerController* PlayerController, TScriptInterface<IDialogueActor> Npc, TSoftObjectPtr<UDialogueStage> Stage);

	void triggerPauseGame(APlayerController* PlayerController);

	bool hideDialogue(APlayerController* PlayerController);

	bool showPauseMenu(APlayerController* controller);

	bool hidePauseMenu(APlayerController* PlayerController);

	bool hideInventoryMenu(APlayerController* PlayerController);
	
	inline bool canOpenInventoryMenu() {
		return IsValid(InventoryMenuClass);
	}

	inline bool canOpenPauseMenu() {
		return IsValid(PauseMenuWidgetClass);
	}

	inline bool canOpenDialogue() {
		return IsValid(DialogueWidgetClass);
	}

	inline bool isInventoryMenuOpen() {
		return IsValid(InventoryMenuWidget);
	}

	inline bool isPauseMenuOpen() {
		return IsValid(PauseMenuWidget);
	}

	inline bool isDialogueOpen() {
		return IsValid(DialogueWidget);
	}
};
