// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Inventory/Loot/Loot.h"
#include "Item.generated.h"

class USpudState;
class USpudStateCustomData;
/**
 * 
 */
UCLASS()
class SUPERHERO_API UItem : public ULoot
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
	float Weight = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> WearableMesh;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UMaterialInterface>> OverrideMaterial;
	
	inline const TArray<TSoftObjectPtr<UMaterialInterface>>& getOverrideMaterials() const{
		return OverrideMaterial;
	}
	inline USkeletalMesh* getSkeletalMesh() const {
		return WearableMesh.LoadSynchronous();
	}
	inline bool isSkeletalMeshNull() const {
		return WearableMesh.IsNull();
	}
	inline UStaticMesh* getMesh() const {
		return Mesh.LoadSynchronous();
	}
	inline bool isSkeletal() const {
		return Mesh.IsNull();
	}
	virtual bool use(AActor* target, class UItemInstance* instance) const { return false; };

	virtual bool attackStart(class UItemInstance* instance, bool isPrimary, bool isHeavy) const { return false; };

	virtual bool attackEnd(class UItemInstance* instance, bool isPrimary, bool isHeavy) const { return false; };

	virtual FName getNextAttackAnimMontage(int & state, bool isHeavy) const { return NAME_None; };

	virtual UItemInstance * create(UObject* outer, int count = 1) const;

	virtual class AItemActor* spawn(UWorld* world, class UItemInstance* instance, FTransform trans) const;

	virtual bool setAnyMesh(struct FAnyMesh& m, UObject* outer) const;

	virtual void sample(class UInventory* inv, int count = 1) override;

	virtual void store(class UItemInstance* instance, const USpudState* State, USpudStateCustomData* CustomData) const { };

	virtual void restore(class UItemInstance* instance, USpudState* State, USpudStateCustomData* CustomData) const { };

	virtual void onAddedToInventory(class UItemInstance* instance) const {}

	virtual void onRemovedFromInventory(class UItemInstance* instance) const{}

	virtual float getArmor()const { return 0; }

	virtual float getDamage() const { return 0; }

	void applyMaterials(UMeshComponent * c) const{
		if (c != nullptr) {
			for (int i = 0; i < OverrideMaterial.Num(); i++) {
				if (UMaterialInterface* mat = OverrideMaterial[i].LoadSynchronous()) {
					c->SetMaterial(i, mat);
				}
			}
		}
	}
};
