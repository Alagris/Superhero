// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponItem.h"
#include "Projectiles/ProjectileType.h"
#include "GunItem.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UGunItem : public UWeaponItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BarrelTipSocket = "Tip";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UProjectileType* Projectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool OnlyFireWhenAiming=false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MakeNoise = 1;

	virtual bool attackStart(class UItemInstance* instance, class UCombatComponent* combat, bool isPrimary, bool isHeavy) const;

	virtual bool attackEnd(class UItemInstance* instance, class UCombatComponent* combat, bool isPrimary, bool isHeavy) const;

	virtual void attackTrigger(class UItemInstance* instance, class UCombatComponent* combat, bool isHeavy) const override;

	
	
};
