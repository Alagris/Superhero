// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController* Controller;

	UPROPERTY()
	class AGameHUD* HUD;

	void setupController(class AGameHUD* HUD, APlayerController* controller);

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* LoadButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* DesktopButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> MainMenuLevel;

	UFUNCTION()
	void OnResume();

	UFUNCTION()
	void OnSave();

	UFUNCTION()
	void OnLoad();

	UFUNCTION()
	void OnSettings();

	UFUNCTION()
	void OnMainMenu();

	UFUNCTION()
	void OnDesktop();
};
