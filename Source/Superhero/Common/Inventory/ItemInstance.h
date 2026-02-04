// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Common/Props/Item.h"
#include "ItemInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SUPERHERO_API FItemInstance 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int Count=1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	int EquippedAt = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UItem* ItemType;
};
