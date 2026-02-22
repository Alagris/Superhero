// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"
#include <Common/Inventory/ClothingSystem.h>

bool UWeaponItem::use(AActor* target, UItemInstance* instance) const
{
	UClothingSystem* c = target->GetComponentByClass<UClothingSystem>();
	if (IsValid(c)) {
		if (!instance->IsOwnedBy(c)) {
			instance->takeFromOwner();
		}
		if (instance->EquippedAt == EQUIPPED_AT_NONE) {
			equip(instance, c, LeftHand);
		}
		else if (instance->EquippedAt == EQUIPPED_AT_RIGHT_HAND) {
			unequip(instance, c, false);
		}
		else if (instance->EquippedAt == EQUIPPED_AT_LEFT_HAND) {
			unequip(instance, c, true);
		}
		return true;
	}
	return false;
}

void UWeaponItem::restore(UItemInstance* instance, USpudState* State, USpudStateCustomData* CustomData) const
{
	if (instance->EquippedAt != -1 && IsValid(instance->Owner)) {
		if (UClothingSystem* c = Cast<UClothingSystem>(instance->Owner)) {
			if (instance->EquippedAt == EQUIPPED_AT_RIGHT_HAND) {
				equip(instance, c, false);
			}
			else if (instance->EquippedAt == EQUIPPED_AT_LEFT_HAND) {
				equip(instance, c, true);
			}
		}
	}
}

void UWeaponItem::equip(UItemInstance* instance, UClothingSystem* c, bool leftHand) const
{
	c->EquipHand(instance, leftHand, HandleSocket, LocomotionStyle);
}

void UWeaponItem::unequip(UItemInstance* instance, UClothingSystem* c, bool leftHand) const
{
	c->UnequipHand(leftHand);
}
