// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Inventory/Health.h"
#include "SurvivalHealth.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API USurvivalHealth : public UHealth
{
	GENERATED_BODY()

public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Dirtiness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Exhaustion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lust;


};
