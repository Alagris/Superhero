// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.h"
#include "Any/AnyMesh.h"
#include "Common/Props/ClothingItem.h"
#include "ClothingSystem.generated.h"

class UItemInstance;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnItemEquippedSignature, const UClothingItem* /*type*/, class UItemInstance* /*item*/, class UClothingSystem* /* inventory */);


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


USTRUCT(BlueprintType)
struct SUPERHERO_API FEquippedHand 
{
	GENERATED_BODY()
public:
	FEquippedHand() {}
	FEquippedHand(FName socketName) :SocketName(socketName) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	UPROPERTY(BlueprintReadOnly)
	UItemInstance* Item;

	UPROPERTY(BlueprintReadOnly)
	FAnyMesh Mesh;

	UPROPERTY(BlueprintReadOnly)
	int LocomotionStyle;

	void* CustomData = nullptr;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UClothingSystem : public UInventory
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
	virtual bool EnsureLootInitialized() override {
		if (Super::EnsureLootInitialized()) {
			autoEquip();
			return true;
		}
		return false;
	}
	
	virtual void UnequipHand(bool leftHand);

	virtual FEquippedHand& EquipHand(UItemInstance* item, bool leftHand, const FName& itemSocket=NAME_None, int locomotionStyle=0);

	virtual void Equip(const UClothingItem* type, UItemInstance* item, bool fireEvents=true);

	virtual void Unequip(const UClothingItem* type, UItemInstance* item, bool fireEvents = true);

	virtual void UnequipAll(bool fireEvents = true);

	void ForceUnequip(UItemInstance* item, bool fireEvents = true) {
		if (item->EquippedAt >= 0) {
			RemoveClothingMesh(item, fireEvents);
		}
		else if (item->EquippedAt == EQUIPPED_AT_RIGHT_HAND) {
			UnequipHand(false);
		}
		else if (item->EquippedAt == EQUIPPED_AT_LEFT_HAND) {
			UnequipHand(true);
		}
	}

	void UnequipHands() {
		UnequipHand(true);
		UnequipHand(false);
	}

	FOnItemEquippedSignature ItemEquippedListeners;

	FOnItemEquippedSignature ItemUnequippedListeners;

	UPROPERTY()
	TArray<FEquippedClothes> ClothesMeshes;

	UPROPERTY()
	USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FEquippedHand HandL = FEquippedHand("l_hand_anchorSocket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FEquippedHand HandR = FEquippedHand("r_hand_anchorSocket");


	FEquippedHand& getHand(bool leftHand) {
		return leftHand ? HandL : HandR;
	}

	UItemInstance* getEquippedInLeftHand() const {
		return HandL.Item;
	}

	UItemInstance* getEquippedInRightHand() const {
		return HandR.Item;
	}

	bool canEquipClothes(const UClothingItem* type) const
	{
		return (OccupiedClothingSlots & uint8(type->Slot)) == 0;
	}

	bool canUnequipClothes(const UClothingItem* item) const
	{
		return !item->IsDevious;
	}

	void autoEquip();

	virtual void onItemCompleteRemoval(UItemInstance* item, bool fireEvents) override {
		ForceUnequip(item, fireEvents);
	}

	virtual void clearInventory() override {
		UnequipAll(false);
		UnequipHands();
		Super::clearInventory();
	}


private:
	void RemoveClothingMesh(UItemInstance* item, bool fireEvents);

	

};
