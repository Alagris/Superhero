// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Common/Props/Item.h"
#include "ISpudObject.h"
#include "ItemInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SUPERHERO_API UItemInstance : public UObject, public ISpudObject
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame,EditAnywhere, BlueprintReadWrite)
	int Count=1;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadOnly)
	int EquippedAt = -1;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadOnly)
	float Durability = -1;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<const UItem> ItemType;

	UPROPERTY(BlueprintReadOnly)
	class UInventory* Owner;

	bool IsOwnedBy(class UInventory* o) {
		return o == Owner;
	}
	inline bool use(AActor * target) {
		return ItemType->use(target, this);
	}

	inline void takeFromOwner();

	inline UItemInstance* popCount(UObject* outer, int count = 1, bool spawnPopped = true) {
		if (Count > count) {
			Count -= count;
			return spawnPopped ? ItemType->spawn(outer, count) : nullptr;
		}
		else {
			EquippedAt = -1;
			return this;
		}
	}


	void store(class UInventory* user, const USpudState* State, USpudStateCustomData* CustomData) {
		CustomData->WriteInt(Count);
		CustomData->WriteFloat(Durability);
		CustomData->WriteInt(EquippedAt);
		CustomData->Write(ItemType);
		ItemType->store(this, State, CustomData);
	}

	void restore(class UInventory* user, USpudState* State, USpudStateCustomData* CustomData) {
		Owner = user;
		bool b = CustomData->ReadInt(Count);
		check(b);
		b = CustomData->ReadFloat(Durability);
		check(b);
		b = CustomData->ReadInt(EquippedAt);
		check(b);
		b = CustomData->Read(ItemType);
		check(b);
		ItemType->restore(this, State, CustomData);
	}
};
