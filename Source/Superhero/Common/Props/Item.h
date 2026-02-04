// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Value = 0;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInterface> OverrideMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int OverrideMaterialSlot = 0;

	virtual void use(class UInventory* inv, struct FItemInstance& instance) {};
};
