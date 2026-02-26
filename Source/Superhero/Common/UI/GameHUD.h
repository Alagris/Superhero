// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Dialogue/Dialogue.h"
#include "PauseMenu/PauseMenu.h"
#include "Status/Status.h"
#include "CharacterMenu/CharacterMenu.h"
#include "Inventory/InventoryMenu.h"
#include "Common/Input/UIInputMappingContext.h"
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
	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	bool PauseGameWhenInInventory=false;

	UPROPERTY()
	UUIInputMappingContext* UIInput;

	UPROPERTY()
	UInputMappingContext* GameInput;

	void setGameInputMapping();

	void TriggerPauseGame(const struct FInputActionValue& Value) {
		triggerPauseGame();
	}

	void TriggerInventory(const struct FInputActionValue& Value) {
		triggerInventory();
	}

	UInventoryMenu* showInventoryMenu( class UInventory* player, class UInventory* npc = nullptr, bool exchangeForFree = false, EInventoryPage page = EInventoryPage::PLAYER);

	bool showCharacterMenu( class AIndoorsSuperhero * Hero);

	bool showDialogue(class UDialogueComponent* Npc, TSoftObjectPtr<UDialogueStage> Stage=nullptr);

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
			if (!anyOpen) {
				setGameInputMapping();
			}
		}
	}
};
