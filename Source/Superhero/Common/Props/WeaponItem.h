// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Props/Item.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UWeaponItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> RiggedMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int LocomotionStyle = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool LeftHand = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName HandleSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ShootingAnim;

	virtual float getDamage() const { return Damage; }

	virtual bool use(AActor* target, class UItemInstance* instance) const override;

	virtual FName getNextAttackAnimMontage(int& state, bool isHeavy) const override { return ShootingAnim; };

	virtual void restore(class UItemInstance* instance, class USpudState* State, class USpudStateCustomData* CustomData) const override;

	virtual void equip(UItemInstance* instance, class UClothingSystem* c, bool leftHand) const;

	virtual void unequip(UItemInstance* instance, class UClothingSystem* c, bool leftHand) const;
};
