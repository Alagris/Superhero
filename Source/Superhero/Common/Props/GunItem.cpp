// Fill out your copyright notice in the Description page of Project Settings.


#include "GunItem.h"
#include "Common/Inventory/ItemInstance.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Props/Actor/ItemActorProjectile.h"
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
    if (OnlyFireWhenAiming) {
        if (!combat->IsAiming()) {
            return;
        }
    }
    FTransform t;
    if (BarrelTipSocket.IsValid()) {
        
        if (!instance->getSocketTransform(BarrelTipSocket, t)) {
            return;
        }
    }
    else if(UInventory * owner = instance->Owner){
        t = owner->GetOwner()->GetActorTransform();
    }
    if (IsValid(instance->SceneComp)) {
        if (IsValid(FireSound)) {
            FVector loc = instance->SceneComp->GetComponentLocation();
            UGameplayStatics::PlaySoundAtLocation(instance->SceneComp, FireSound, loc);
        }
    }
    spawnProjectile(instance, isHeavy, t);
}

AActor* UGunItem::spawnProjectile(UItemInstance* instance, bool isHeavy, FTransform & trans) const
{
    AItemActorProjectile * p = AItemActorProjectile::spawn(instance->GetWorld(), instance, trans);
    p->shoot(instance->Owner == nullptr ? nullptr : instance->Owner->GetOwner(), instance, ProjectileVelocity, ProjectileGravity);
    return p;
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
