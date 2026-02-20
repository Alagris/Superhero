// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/ItemInstance.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Props/Actor/ItemActorStatic.h"

UItemInstance* UItemInstance::remove(int quantity, bool spawnPopped)
{
	if (IsValid(Owner)) {
		return Owner->removeItem(ItemType, quantity, spawnPopped);
	}
	return nullptr;
}

class AItemActor* UItemInstance::drop(int quantity, AActor* target)
{
	if (IsValid(Owner)) {
		return Owner->dropItem(ItemType, quantity, target);
	}
	return nullptr;
}

UItemInstance* UItemInstance::takeFromOwner()
{
	if (IsValid(Owner)) {
		return Owner->removeInstance(this);
	}
	return nullptr;
}

