// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Recipe.generated.h"


USTRUCT(BlueprintType)
struct SUPERHERO_API FIngredient
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const class UItem* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Quantity;


};


/**
 *
 */
UCLASS(BlueprintType)
class SUPERHERO_API URecipe : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* CraftSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const class UItem * OutputItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int OutputQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FIngredient> Ingredients;

	UFUNCTION()
	virtual void make(class UInventory* inv) const;

	UFUNCTION()
	bool canMake(class UInventory* inv) const;
	
};

