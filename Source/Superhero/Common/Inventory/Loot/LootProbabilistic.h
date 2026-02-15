// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Inventory/Loot/Loot.h"
#include "structs/LootItemChance.h"
#include "LootProbabilistic.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API ULootProbabilistic : public ULoot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MinQuantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxQuantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FLootItemChance> Items;


	virtual void sample(UInventory* inv, int count) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void update();
};
