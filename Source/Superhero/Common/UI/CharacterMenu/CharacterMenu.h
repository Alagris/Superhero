// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "CharacterMenu.generated.h"

class AIndoorsSuperhero;
class APlayerController;
class AGameHUD;
/**
 * 
 */
UCLASS()
class SUPERHERO_API UCharacterMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void setup(AGameHUD *hud, APlayerController* PlayerController, AIndoorsSuperhero* Hero);

	APlayerController* PlayerController;
	AIndoorsSuperhero* Hero;
	AGameHUD* Hud;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HeroName;


	UPROPERTY(meta = (BindWidget))
	UButton* TalkButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GiveButton;


	UFUNCTION()
	void OnTalkClick();

	UFUNCTION()
	void OnGiveClick();
};
