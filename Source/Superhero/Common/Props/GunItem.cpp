// Fill out your copyright notice in the Description page of Project Settings.


#include "GunItem.h"
#include "Common/Inventory/ItemInstance.h"
#include "Common/Inventory/Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Common/Combat/CombatComponent.h"
#include "Common/Character/Movement/AdvancedMovementComponent.h"

bool UGunItem::attackEnd(UItemInstance* instance, class UCombatComponent* combat, bool isPrimary, bool isHeavy) const
{
    if (IsValid(instance->Owner)) {
        if (isPrimary) {
            combat->setNotWantsToAttack();
        }
        else {
            combat->endAiming();
        }
    }
    return true;
}

void UGunItem::attackTrigger(UItemInstance* instance, class UCombatComponent* combat, bool isHeavy) const
{
    Super::attackTrigger(instance, combat, isHeavy);
    if (IsValid(Projectile)) {
        if (OnlyFireWhenAiming) {
            if (!combat->IsAiming()) {
                return;
            }
        }
        if (MakeNoise > 0) {
            if (APawn* p = Cast<APawn>(instance->getActorOwner())) {
                p->MakeNoise(MakeNoise,p,p->GetActorLocation());
            }
        }
        Projectile->shootFromItemSocket(BarrelTipSocket, instance);
    }
}



bool UGunItem::attackStart(UItemInstance* instance, class UCombatComponent* combat, bool isPrimary, bool isHeavy) const
{
    if (IsValid(instance->Owner)) {
        if (isPrimary) {
            combat->setWantsToAttack(instance, combat->getCombo(ComboId), isPrimary, isHeavy);
        }
        else {
            combat->startAiming();
        }
    }
    return true;
}
