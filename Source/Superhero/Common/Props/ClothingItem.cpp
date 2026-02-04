// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Props/ClothingItem.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"


void UClothingItem::use(UInventory* inv, FItemInstance& instance)
{
	if (instance.EquippedAt == -1) {
		inv->ItemEquippedListeners.Broadcast(this, instance, inv);
	}
	else {
		inv->ItemUnequippedListeners.Broadcast(this, instance, inv);
	}
}
