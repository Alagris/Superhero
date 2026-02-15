// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/Loot/LootProbabilistic.h"
#include "Common/Inventory/Inventory.h"
#include "Algo/BinarySearch.h"

#if WITH_EDITOR
void ULootProbabilistic::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property != NULL)
	{
		const FName& PropertyName = PropertyChangedEvent.GetMemberPropertyName();

		if (PropertyName == "Items")
		{
			update();
		}
	}
}
#endif
void ULootProbabilistic::sample(UInventory* inv, int count)
{
	int n = Items.Num();
	if (n > 0) {
		float total = Items[n - 1].AccumulativeLikelihood;
		float l = FMath::FRandRange(0, total);
		int idx = Algo::UpperBound(Items, l);
		check(idx >= 0);
		check(idx < n);
		ULoot* item = Items[idx].Item.LoadSynchronous();
		item->sample(inv, count);
	}
}

void ULootProbabilistic::update()
{
	float a = 0;
	for (auto& i : Items) {
		a += i.Likelihood;
		i.AccumulativeLikelihood = a;
	}
}
