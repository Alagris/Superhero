// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Props/Item.h"
#include "GunItem.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UGunItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> RiggedMesh;

	
};
