// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraGunItem.h"
#include "NiagaraFunctionLibrary.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"

#include <Common/Inventory/ClothingSystem.h>
#include "Actor/ItemActorNiagaraProjectile.h"

AActor* UNiagaraGunItem::spawnProjectile(UItemInstance* instance, bool isHeavy, FTransform& trans) const
{
    AItemActorNiagaraProjectile* p = AItemActorNiagaraProjectile::spawn(instance->GetWorld(), Trail, trans, ImpactExplosion);
    p->Movement->ProjectileGravityScale = 0;
    //Movement->Bounciness = 0.1f;
    //p->Movement->Friction = 0.5f;
    p->CollisionSphere->SetSimulatePhysics(SimulatePhysics);
    p->CollisionSphere->SetEnableGravity(EnableGravity);
    p->Movement->MaxSpeed = MaxSpeed;
    AActor* shooter = instance->Owner == nullptr ? nullptr : instance->Owner->GetOwner();
    p->shoot(shooter, instance, ProjectileVelocity, ProjectileGravity, MuzzleFlash);
    return p;
}
