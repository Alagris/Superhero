// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Dialogue/Dialogue.h"
#include "PauseMenu/PauseMenu.h"
#include "Status/Status.h"
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

	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UDialogue> DialogueWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UPauseMenu> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UCharacterMenu> CharacterMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UInventoryMenu> InventoryMenuClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStatus> StatusWidget;

	UPROPERTY()
	TObjectPtr<UDialogue> DialogueWidget;

	UPROPERTY()
	TObjectPtr<UPauseMenu> PauseMenuWidget;

	UPROPERTY()
	TObjectPtr<UCharacterMenu> CharacterMenuWidget;

	UPROPERTY()
	TObjectPtr<UInventoryMenu> InventoryMenuWidget;

public:
	void TriggerPauseGame(const struct FInputActionValue& Value) {
		triggerPauseGame();
	}

	void TriggerInventory(const struct FInputActionValue& Value) {
		triggerInventory();
	}

	bool showInventoryMenu( class UInventory* Inv);

	bool showCharacterMenu( class AIndoorsSuperhero * Hero);

	bool showDialogue( TScriptInterface<IDialogueActor> Npc, TSoftObjectPtr<UDialogueStage> Stage);

	void triggerInventory();

	void triggerPauseGame();

	bool hideDialogue();

	bool showPauseMenu();

	bool hidePauseMenu();

	bool hideInventoryMenu();
	
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
private:
	void setStatus() {
		if (IsValid(StatusWidget)) {
			bool anyOpen = isDialogueOpen()
				|| isInventoryMenuOpen()
				|| isPauseMenuOpen();

			StatusWidget->SetVisibility(anyOpen ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
		}
	}
};
