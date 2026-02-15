// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Props/Item.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"

UItemInstance * UItem::spawn(UObject* outer, int count) const
{
	UItemInstance * p = NewObject<UItemInstance>(outer, UItemInstance::StaticClass());
	p->ItemType = this;
	p->Count = count;
	//p->Durability = Durability;
	return p;
}

void UItem::sample(UInventory* inv, int count)
{
	if (count > 0) {
		inv->addItem(spawn(inv->GetWorld(), count));
	}
}
