// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/Inventory/InventoryMenu.h"

bool UInventoryMenu::setup(AGameHUD* hud, APlayerController* PlayerController, UInventory* inv)
{
	Inv = inv;
	return false;
}
