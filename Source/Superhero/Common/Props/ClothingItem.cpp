// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Props/ClothingItem.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"
#include <Common/Inventory/ClothingSystem.h>


bool UClothingItem::use(AActor* target, UItemInstance * instance) const
{
	UClothingSystem* c = target->GetComponentByClass<UClothingSystem>();
	if (IsValid(c)) {
		if (!instance->IsOwnedBy(c->inventory)) {
			instance->takeFromOwner();
		}
		if (instance->EquippedAt == -1) {
			c->Equip(this, instance);
		}
		else {
			c->Unequip(this, instance);
		}
		return true;
	}
	return false;
	
}

void UClothingItem::restore(UItemInstance* instance,class USpudState* State, class USpudStateCustomData* CustomData) const
{
	if (instance->EquippedAt>-1 && IsValid(instance->Owner)) {
		UClothingSystem* c = instance->Owner->GetOwner()->GetComponentByClass<UClothingSystem>();
		if (IsValid(c)) {
			c->Equip(this, instance, false);
		}
	}
}

void UClothingItem::onRemovedFromInventory(UItemInstance* instance) const
{
	if (IsValid(instance->Owner)) {
		UClothingSystem* c = instance->Owner->GetOwner()->GetComponentByClass<UClothingSystem>();
		if (IsValid(c)) {
			c->Unequip(this, instance);
		}
	}
}
