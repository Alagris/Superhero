// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/CharacterMenu/CharacterMenu.h"
#include "Common/UI/GameHUD.h"
#include "Indoors/IndoorsSuperhero.h"
#include "Indoors/IndoorsPlayerController.h"

void UCharacterMenu::setup(AGameHUD* hud, APlayerController* c, AIndoorsSuperhero* h)
{
	this->Hud = hud;
	this->Hero = h;
	this->PlayerController = c;
}

void UCharacterMenu::OnTalkClick()
{
	Hud->showDialogue(Hero, Hero->DialogueStage);
}

void UCharacterMenu::OnGiveClick()
{

}
