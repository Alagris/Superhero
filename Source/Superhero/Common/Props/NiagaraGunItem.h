// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Props/GunItem.h"
#include "NiagaraSystem.h"
#include "NiagaraGunItem.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UNiagaraGunItem : public UGunItem
{
	GENERATED_BODY()
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* ImpactExplosion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* Trail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool SimulatePhysics=false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool EnableGravity=false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSpeed=100000;


	virtual AActor* spawnProjectile(class UItemInstance* instance, bool isHeavy, FTransform& trans) const override;
};
