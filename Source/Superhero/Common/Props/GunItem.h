// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Props/WeaponItem.h"
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
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ProjectileGravity=0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector ProjectileVelocity = FVector(6000,0,0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool OnlyFireWhenAiming=false;

	virtual bool attackStart(class UItemInstance* instance, class UCombatComponent* combat, bool isPrimary, bool isHeavy) const;

	virtual bool attackEnd(class UItemInstance* instance, class UCombatComponent* combat, bool isPrimary, bool isHeavy) const;

	virtual void attackTrigger(class UItemInstance* instance, class UCombatComponent* combat, bool isHeavy) const override;

	virtual AActor * spawnProjectile(class UItemInstance* instance, bool isHeavy, FTransform & trans) const;
};
