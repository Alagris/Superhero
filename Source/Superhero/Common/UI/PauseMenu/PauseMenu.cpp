// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/PauseMenu/PauseMenu.h"
#include "Common/UI/GameHUD.h"
#include "SpudSubsystem.h"
#include <Kismet/GameplayStatics.h>

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnResume);
	SaveButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnSave);
	LoadButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnLoad);
	SettingsButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnSettings);
	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnMainMenu);
	DesktopButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::OnDesktop);
}

void UPauseMenu::setupController(AGameHUD* hud,APlayerController* controller)
{
	Controller = controller;
	this->HUD = hud;
}

void UPauseMenu::OnResume()
{
	if (IsValid(Controller)) {
		HUD->hidePauseMenu();
	}
}

void UPauseMenu::OnSave()
{
	USpudSubsystem* SpudSystem = GetSpudSubsystem(GetWorld());
	SpudSystem->QuickSaveGame();
}

void UPauseMenu::OnLoad()
{
	USpudSubsystem* SpudSystem = GetSpudSubsystem(GetWorld());
	SpudSystem->QuickLoadGame();
}

void UPauseMenu::OnSettings()
{

	if (APostProcessVolume* ppv = Cast<APostProcessVolume>(UGameplayStatics::GetActorOfClass(Controller->Player, APostProcessVolume::StaticClass()))) {
		ppv->bEnabled = ~ppv->bEnabled;
	}

}

void UPauseMenu::OnMainMenu()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
}

void UPauseMenu::OnDesktop()
{
	UWorld* w = Controller->GetWorld();
	UKismetSystemLibrary::QuitGame(w, Controller, EQuitPreference::Type::Quit, false);
}
