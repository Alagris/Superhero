// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.h"
#include "Common/Props/ClothingItem.h"
#include "ClothingSystem.generated.h"

class UItemInstance;

USTRUCT(BlueprintType)
struct SUPERHERO_API FEquippedClothes
{
	GENERATED_BODY()
public:
	FEquippedClothes() {}
	FEquippedClothes(TObjectPtr<USkeletalMeshComponent> m, const UClothingItem* t, UItemInstance* i):Mesh(m), ItemType(t), Item(i){}

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY()
	const UClothingItem* ItemType;

	UPROPERTY()
	UItemInstance* Item;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UClothingSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClothingSystem()
	{
		PrimaryComponentTick.bCanEverTick = false;
		bWantsInitializeComponent = true;
	}
protected:

	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	uint8 OccupiedClothingSlots = 0;
	uint8 OccupiedDeviousClothingSlots = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void destroySkeletalMeshComponent(USkeletalMeshComponent* comp);
	USkeletalMeshComponent* createSkeletalMeshComponent(USkeletalMesh* mesh);


	void Equip(const UClothingItem* type, UItemInstance* item, bool fireEvents=true);

	void Unequip(const UClothingItem* type, UItemInstance* item, bool fireEvents = true);

	void UnequipAll(bool fireEvents = true);

	UPROPERTY()
	TArray<FEquippedClothes> ClothesMeshes;

	UPROPERTY()
	UInventory* inventory;

	UPROPERTY()
	USkeletalMeshComponent* CharacterMesh;
	

	bool canEquipClothes(const UClothingItem* type) const
	{
		return (OccupiedClothingSlots & uint8(type->Slot)) == 0;
	}

	bool canUnequipClothes(const UClothingItem* item) const
	{
		return !item->IsDevious;
	}

	void autoEquip();
private:
	void RemoveItem(UItemInstance* item, bool fireEvents);

	void OnInventoryCleared(UInventory* inv) {
		UnequipAll(false);
	}

};
