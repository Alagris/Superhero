// Fill out your copyright notice in the Description page of Project Settings.


#include "GunItem.h"
#include "Common/Inventory/ItemInstance.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Character/Movement/AdvancedMovementComponent.h"

bool UGunItem::attackEnd(UItemInstance* instance, bool isPrimary, bool isHeavy) const
{
   
    if (IsValid(instance->Owner)) {
        if (UAdvancedMovementComponent* m = instance->Owner->GetOwner()->GetComponentByClass<UAdvancedMovementComponent>()) {
            if (isPrimary) {
                m->setNotWantsToAttack();
            }
            else {
                m->endAiming();
            }
        }
    }
    return true;
}

bool UGunItem::attackStart(UItemInstance* instance, bool isPrimary, bool isHeavy) const
{
    
    if (IsValid(instance->Owner)) {
        if (UAdvancedMovementComponent* m = instance->Owner->GetOwner()->GetComponentByClass<UAdvancedMovementComponent>()) {
            if (isPrimary) {
                m->setWantsToAttack(instance, isHeavy);
            }
            else {
                m->startAiming();
            }
        }
    }
    return true;
}
