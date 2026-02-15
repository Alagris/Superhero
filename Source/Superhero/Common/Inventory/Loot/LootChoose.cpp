// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/Loot/LootChoose.h"
#include "Common/Inventory/Inventory.h"

void ULootChoose::sample(UInventory* inv, int count)
{
	if (count > 0 && Items.Num() > 0) {
		UWorld* world = inv->GetWorld();
		int quantity = FMath::RandRange(MinQuantity, MaxQuantity);
		for (int i = 0; i < quantity; i++) {
			int idx = FMath::RandRange(0, Items.Num() - 1);
			TSoftObjectPtr<ULoot> item = Items[idx];
			ULoot* loaded = item.LoadSynchronous();
			if (loaded != nullptr) {
				loaded->sample(inv, count);
			}
		}
	}
}
