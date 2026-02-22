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
			c->EquipHand(instance, LeftHand, HandleSocket, LocomotionStyle);
		}
		else if (instance->EquippedAt == EQUIPPED_AT_RIGHT_HAND) {
			c->UnequipHand(false);
		}
		else if (instance->EquippedAt == EQUIPPED_AT_LEFT_HAND) {
			c->UnequipHand(true);
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
				c->EquipHand(instance, false, HandleSocket, LocomotionStyle);
			}
			else if (instance->EquippedAt == EQUIPPED_AT_LEFT_HAND) {
				c->EquipHand(instance, true, HandleSocket, LocomotionStyle);
			}
		}
	}
}
