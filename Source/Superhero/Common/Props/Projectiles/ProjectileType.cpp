// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileType.h"
#include "Common/Props/Actor/ItemActorProjectile.h"

AActor* UProjectileType::shootProjectile(AActor* shooter, UItemInstance* instance, FTransform& trans) const
{
    
    playFireSound(instance->SceneComp, trans);

    AItemActorProjectile* p = AItemActorProjectile::spawn(instance->GetWorld(), instance, trans);
    p->shoot(shooter, instance, ProjectileVelocity, ProjectileGravity);
    return p;
}