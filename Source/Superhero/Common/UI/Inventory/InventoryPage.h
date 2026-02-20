// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryPage.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EInventoryPage : uint8
{
	PLAYER =0 UMETA(DisplayName = "Player"),
	NPC =1 UMETA(DisplayName = "Npc"),
	CRAFTING =2 UMETA(DisplayName = "Crafting"),

};