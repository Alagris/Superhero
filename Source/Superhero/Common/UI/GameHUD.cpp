// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/GameHUD.h"
#include <EnhancedInputSubsystems.h>


void AGameHUD::BeginPlay()
{
	UIInput = NewObject<UUIInputMappingContext>(this);
	UIInput->initialize(GetOwningPlayerController());
	if (StatusWidget) {
		StatusWidget->AddToViewport(999);
	}


}

void AGameHUD::setGameInputMapping()
{
	if (IsValid(GameInput)) {
		APlayerController* PlayerController = GetOwningPlayerController();
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(GameInput, 0);
		}
	}
}

UInventoryMenu * AGameHUD::showInventoryMenu(UInventory* player, UInventory* npc, bool exchangeForFree, EInventoryPage page)
{
	
	if (InventoryMenuWidget == nullptr && IsValid(InventoryMenuClass)) {
		APlayerController* PlayerController = GetOwningPlayerController();
		InventoryMenuWidget = CreateWidget<UInventoryMenu>(GetWorld(), InventoryMenuClass);
		InventoryMenuWidget->setup(this, PlayerController, player, npc, exchangeForFree, page);
		InventoryMenuWidget->AddToViewport(9998); // Z-order, this just makes it render on the very top.
		InventoryMenuWidget->SetKeyboardFocus();

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		//Mode.SetWidgetToFocus(InventoryMenuWidget->TakeWidget());
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetPause(PauseGameWhenInInventory);
		setStatus();
		return InventoryMenuWidget;
	}
	return nullptr;
}

bool AGameHUD::showCharacterMenu( AIndoorsSuperhero* Hero)
{
	if (CharacterMenuWidget == nullptr && IsValid(CharacterMenuWidgetClass)) {
		APlayerController* PlayerController = GetOwningPlayerController();
		CharacterMenuWidget = CreateWidget<UCharacterMenu>(GetWorld(), CharacterMenuWidgetClass);
		CharacterMenuWidget->setup(this, PlayerController, Hero);
		CharacterMenuWidget->AddToViewport(9998); // Z-order, this just makes it render on the very top.
		CharacterMenuWidget->SetKeyboardFocus();

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		//Mode.SetWidgetToFocus(CharacterMenuWidget->TakeWidget());
		PlayerController->SetInputMode(Mode);
		setStatus();
	}
	return false;
}

bool AGameHUD::showDialogue(class UDialogueComponent * Npc, TSoftObjectPtr<UDialogueStage> Stage)
{
	if (DialogueWidget == nullptr && IsValid(DialogueWidgetClass)) {
		APlayerController* PlayerController = GetOwningPlayerController();
		DialogueWidget = CreateWidget<UDialogue>(GetWorld(), DialogueWidgetClass);
		DialogueWidget->setup(this, PlayerController, Npc, Stage);
		DialogueWidget->AddToViewport(9998); // Z-order, this just makes it render on the very top.
		DialogueWidget->SetKeyboardFocus();

		FInputModeUIOnly Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetWidgetToFocus(DialogueWidget->TakeWidget());
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(true);
		setStatus();
		return true;
		
	}
	return false;
}

void AGameHUD::triggerInventory()
{
	if (!isPauseMenuOpen()) {
		if (isInventoryMenuOpen()) {
			hideInventoryMenu();
		}
		else {
			if (UInventory* inv = GetOwningPawn()->GetComponentByClass<UInventory>()) {
				showInventoryMenu(inv);
			}
		}
	}
}
void AGameHUD::triggerPauseGame()
{
	if (isInventoryMenuOpen()) {
		hideInventoryMenu();
	}
	else if (isDialogueOpen()) {
		hideDialogue();
	}
	else if (isPauseMenuOpen()) {
		hidePauseMenu();
	}
	else {
		showPauseMenu();
	}
}
bool AGameHUD::hideDialogue()
{
	if (DialogueWidget != nullptr) {
		APlayerController* PlayerController = GetOwningPlayerController();
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
		FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(false);
		setStatus();
		return true;

	}
	return false;
}

bool AGameHUD::showPauseMenu()
{
	if (PauseMenuWidget == nullptr && IsValid(PauseMenuWidgetClass)) {
		APlayerController* controller = GetOwningPlayerController();
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
		setStatus();
		return true;
	}
	return false;
}

bool AGameHUD::hidePauseMenu()
{
	if (PauseMenuWidget != nullptr) {
		APlayerController* PlayerController = GetOwningPlayerController();
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;
		FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetPause(false);
		setStatus();
		return true;
	}
	return false;
}

bool AGameHUD::hideInventoryMenu()
{
	if (InventoryMenuWidget != nullptr) {
		APlayerController* PlayerController = GetOwningPlayerController();
		InventoryMenuWidget->unbindInventories();
		InventoryMenuWidget->RemoveFromParent();
		InventoryMenuWidget = nullptr;
		FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetPause(false);
		setStatus();
		return true;
	}
	return false;
}