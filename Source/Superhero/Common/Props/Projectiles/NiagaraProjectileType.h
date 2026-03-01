// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraSystem.h"
#include "ProjectileType.h"
#include "NiagaraProjectileType.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UNiagaraProjectileType : public UProjectileType
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
	bool SimulatePhysics = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool EnableGravity = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSpeed = 100000;

	virtual AActor* shootProjectile(AActor* shooter, class UItemInstance* instance, FTransform& trans) const override;
};
