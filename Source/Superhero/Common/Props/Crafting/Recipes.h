// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Recipe.h"
#include "Recipes.generated.h"




/**
 *
 */
UCLASS(BlueprintType)
class SUPERHERO_API URecipes : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<URecipe*> Recipes;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* CraftSound;
};

