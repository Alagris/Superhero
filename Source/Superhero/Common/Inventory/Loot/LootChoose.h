// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Inventory/Loot/Loot.h"
#include "LootChoose.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API ULootChoose : public ULoot
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MinQuantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxQuantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<ULoot>> Items;


	virtual void sample(class UInventory* inv, int count) override;
};
