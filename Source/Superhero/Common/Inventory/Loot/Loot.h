// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Loot.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API ULoot : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void sample(class UInventory* inv, int count = 1) {}
};
