// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/ItemInstance.h"
#include "Common/Inventory/Inventory.h"

inline void UItemInstance::takeFromOwner()
{
	if (IsValid(Owner)) {
		Owner->removeItem(this);
	}
}
