// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Common/Props/Item.h"
#include "ISpudObject.h"
#include "ItemInstance.generated.h"

#define EQUIPPED_AT_PROJECTILE -5
#define EQUIPPED_AT_DOUBLEHANDED -4
#define EQUIPPED_AT_NONE -1
#define EQUIPPED_AT_LEFT_HAND -2
#define EQUIPPED_AT_RIGHT_HAND -3
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
	int EquippedAt = EQUIPPED_AT_NONE;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadOnly)
	float Durability = -1;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<const UItem> ItemType;

	UPROPERTY(BlueprintReadOnly)
	class UInventory* Owner;

	UPROPERTY(BlueprintReadOnly)
	class USceneComponent* SceneComp;

	bool getSocketTransform(FName socketName, FTransform & t) {
		if (UStaticMeshComponent* sta = Cast<UStaticMeshComponent>(SceneComp)) {
			t = sta->GetSocketTransform(socketName);
			return true;
		}
		else if (USkeletalMeshComponent* skel = Cast<USkeletalMeshComponent>(SceneComp)) {
			t = skel->GetSocketTransform(socketName);
			return true;
		}
		else {
			return false;
		}
	}
	float getDamageDealt(class UHealth * victim, AActor * attacker, float hitStrength) {
		return ItemType->getDamageDealt(victim, attacker, this, hitStrength);
	}

	void unsetEquipped() {
		EquippedAt = EQUIPPED_AT_NONE;
		SceneComp = nullptr;
	}
	void setEquipped(int idx, class USceneComponent* c) {
		EquippedAt = idx;
		SceneComp = c;
	}
	const FText& getName()const {
		return ItemType->Name;
	}
	const FText& getDescr()const {
		return ItemType->Description;
	}
	bool isSkeletal() const {
		return ItemType->isSkeletal();
	}
	USkeletalMesh* getSkeletalMesh() const {
		return ItemType->getSkeletalMesh();
	}
	UStaticMesh* getMesh() const{
		return ItemType->getMesh();
	}
	inline const TArray<TSoftObjectPtr<UMaterialInterface>>& getOverrideMaterials() const {
		return ItemType->getOverrideMaterials();
	}
	void applyMaterials(UMeshComponent* c) const {
		ItemType->applyMaterials(c);
	}
	bool IsOwnedBy(class UInventory* o) const {
		return o == Owner;
	}
	inline bool use(AActor * target) {
		return ItemType->use(target, this);
	}
	inline bool attackStart(class UCombatComponent* combat, bool isPrimary, bool isHeavy) {
		return ItemType->attackStart(this, combat, isPrimary, isHeavy);
	}
	inline bool attackEnd(class UCombatComponent* combat, bool isPrimary, bool isHeavy) {
		return ItemType->attackEnd(this, combat, isPrimary, isHeavy);
	}
	bool setAnyMesh(struct FAnyMesh& m, UObject* outer) const {
		return ItemType->setAnyMesh(m, outer);
	}
	void attackTrigger(class UCombatComponent* combat, bool isHeavy) {
		ItemType->attackTrigger(this, combat, isHeavy);
	}

	UItemInstance* remove(int quantity = 1, bool spawnPopped = true);

	class AItemActor* drop(int quantity=1, AActor* target=nullptr);

	UItemInstance* takeFromOwner();

	bool isEquipped() {
		return EquippedAt != EQUIPPED_AT_NONE;
	}

	inline UItemInstance* popCount(UObject* outer, int count = 1, bool spawnPopped = true) {
		if (Count > count) {
			Count -= count;
			return spawnPopped ? ItemType->create(outer, count) : nullptr;
		}
		else {
			EquippedAt = EQUIPPED_AT_NONE;
			return this;
		}
	}


	class AItemActor* spawn(UWorld* world, FTransform trans) {
		return ItemType->spawn(world, this, trans);
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
