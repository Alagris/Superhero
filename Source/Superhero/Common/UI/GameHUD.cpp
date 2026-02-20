// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/GameHUD.h"


bool AGameHUD::showInventoryMenu(APlayerController* PlayerController, UInventory* Inv)
{
	if (InventoryMenuWidget == nullptr && IsValid(InventoryMenuClass)) {
		InventoryMenuWidget = CreateWidget<UInventoryMenu>(GetWorld(), InventoryMenuClass);
		InventoryMenuWidget->setup(this, PlayerController, Inv);
		InventoryMenuWidget->AddToViewport(9998); // Z-order, this just makes it render on the very top.
		InventoryMenuWidget->SetKeyboardFocus();

		FInputModeUIOnly Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetWidgetToFocus(InventoryMenuWidget->TakeWidget());
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetPause(true);
	}
	return false;
}

bool AGameHUD::showCharacterMenu(APlayerController* PlayerController, AIndoorsSuperhero* Hero)
{
	if (CharacterMenuWidget == nullptr && IsValid(CharacterMenuWidgetClass)) {
		CharacterMenuWidget = CreateWidget<UCharacterMenu>(GetWorld(), CharacterMenuWidgetClass);
		CharacterMenuWidget->setup(this, PlayerController, Hero);
		CharacterMenuWidget->AddToViewport(9998); // Z-order, this just makes it render on the very top.
		CharacterMenuWidget->SetKeyboardFocus();

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetWidgetToFocus(CharacterMenuWidget->TakeWidget());
		PlayerController->SetInputMode(Mode);
	}
	return false;
}

bool AGameHUD::showDialogue(APlayerController* PlayerController, TScriptInterface<IDialogueActor> Npc, TSoftObjectPtr<UDialogueStage> Stage)
{
	if (DialogueWidget == nullptr && IsValid(DialogueWidgetClass)) {
		DialogueWidget = CreateWidget<UDialogue>(GetWorld(), DialogueWidgetClass);
		DialogueWidget->setup(this, PlayerController, Npc, Stage);
		DialogueWidget->AddToViewport(9998); // Z-order, this just makes it render on the very top.
		DialogueWidget->SetKeyboardFocus();

		FInputModeUIOnly Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetWidgetToFocus(DialogueWidget->TakeWidget());
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(true);
		return true;
		
	}
	return false;
}
void AGameHUD::triggerPauseGame(APlayerController* PlayerController)
{
	if (isDialogueOpen()) {
		hideDialogue(PlayerController);
	}
	else if (isPauseMenuOpen()) {
		hidePauseMenu(PlayerController);
	}
	else {
		showPauseMenu(PlayerController);
	}
}
bool AGameHUD::hideDialogue(APlayerController* PlayerController)
{
	if (DialogueWidget != nullptr) {
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
		FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(false);
		return true;
	}
	return false;
}

bool AGameHUD::showPauseMenu(APlayerController* controller)
{
	if (PauseMenuWidget == nullptr && IsValid(PauseMenuWidgetClass)) {
		PauseMenuWidget = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuWidgetClass);
		PauseMenuWidget->setupController(this, controller);
		PauseMenuWidget->AddToViewport(9999); // Z-order, this just makes it render on the very top.
		PauseMenuWidget->SetKeyboardFocus();

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetWidgetToFocus(PauseMenuWidget->TakeWidget());
		controller->SetInputMode(Mode);
		controller->SetShowMouseCursor(true);
		controller->SetPause(true);
		return true;
	}
	return false;
}

bool AGameHUD::hidePauseMenu(APlayerController* PlayerController)
{
	if (PauseMenuWidget != nullptr) {
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;
		FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetPause(false);
		return true;
	}
	return false;
}

bool AGameHUD::hideInventoryMenu(APlayerController* PlayerController)
{
	if (InventoryMenuWidget != nullptr) {
		if (InventoryMenuWidget->NpcInv != nullptr) {
			InventoryMenuWidget->NpcInv->InventoryWidget = nullptr;
		}
		InventoryMenuWidget->PlayerInv->InventoryWidget = nullptr;
		InventoryMenuWidget->RemoveFromParent();
		InventoryMenuWidget = nullptr;
		FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetPause(false);
		return true;
	}
	return false;
}