// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.h"
#include "Common/Props/ClothingItem.h"
#include "ClothingSystem.generated.h"

USTRUCT(BlueprintType)
struct SUPERHERO_API FEquippedClothes
{
	GENERATED_BODY()
public:
	FEquippedClothes() {}
	FEquippedClothes(TObjectPtr<USkeletalMeshComponent> m, UClothingItem* i):Mesh(m), Item(i){}

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY()
	UClothingItem* Item;
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

	void OnEquip(UClothingItem* type, FItemInstance& item, UInventory* inventory);

	void OnUnequip(UClothingItem* type, FItemInstance& item, UInventory* inventory);

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
private:
	void RemoveItem(UClothingItem* type, FItemInstance& item);
};
