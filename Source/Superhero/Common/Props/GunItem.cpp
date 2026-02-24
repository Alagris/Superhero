// Fill out your copyright notice in the Description page of Project Settings.


#include "GunItem.h"
#include "Common/Inventory/ItemInstance.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Props/Actor/ItemActorProjectile.h"
#include "Kismet/GameplayStatics.h"
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

void UGunItem::attackTrigger(UItemInstance* instance, bool isHeavy) const
{
    Super::attackTrigger(instance, isHeavy);
    if (OnlyFireWhenAiming) {
        if (UAdvancedMovementComponent* m = instance->Owner->GetOwner()->GetComponentByClass<UAdvancedMovementComponent>()) {
            if (!m->IsAiming) {
                return;
            }
        }
    }
    FTransform t;
    if (BarrelTipSocket.IsValid()) {
        
        if (UStaticMeshComponent* sta = Cast<UStaticMeshComponent>(instance->SceneComp)) {
            t = sta->GetSocketTransform(BarrelTipSocket);
        }
        else if (USkeletalMeshComponent* skel = Cast<USkeletalMeshComponent>(instance->SceneComp)) {
            t = skel->GetSocketTransform(BarrelTipSocket);
        }
        else {
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
