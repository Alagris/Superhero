// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Common/Inventory/Inventory.h>
#include "InventoryMenu.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

	
	UPROPERTY()
	UInventory* Inv;
public:
	bool setup(class AGameHUD* hud, APlayerController* PlayerController, UInventory* inv);
};
