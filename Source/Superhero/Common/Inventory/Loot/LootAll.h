// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Inventory/Loot/Loot.h"
#include "structs/LootItem.h"
#include "LootAll.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API ULootAll : public ULoot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FLootItem> Items;


	virtual void sample(class UInventory* inv, int count) override;
};
