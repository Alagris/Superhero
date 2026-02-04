// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Props/Item.h"
#include "ClothingSlot.h"
#include "ClothingItem.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UClothingItem : public UItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> WearableMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsFullBodyReplacement=false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsDevious = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsUnderwear = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EClothingSlot Slot = EClothingSlot::NONE;

	uint8 slot() const{
		return uint8(Slot);
	}
	virtual void use(class UInventory* inv, struct FItemInstance& instance) override;

};
