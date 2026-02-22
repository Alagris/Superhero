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


	virtual bool attackStart(class UItemInstance* instance, bool isPrimary, bool isHeavy) const;

	virtual bool attackEnd(class UItemInstance* instance, bool isPrimary, bool isHeavy) const;

};
