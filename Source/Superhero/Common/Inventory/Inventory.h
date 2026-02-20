// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInstance.h"
#include "ISpudObject.h"
#include "Inventory.generated.h"

class UClothingItem;


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemAddedSignature, class UItemInstance* /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemRemovedSignature, class UItemInstance* /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnItemConsumedSignature, class UItemInstance* /*item*/, int /*consumedCount*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClearInventorySignature, class UInventory * /* inventory */);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UInventory : public UActorComponent, public ISpudObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(SaveGame)
	bool isLootInitialized=false;
public:	

	class UInventoryMenu* InventoryWidget;
	
	virtual bool EnsureLootInitialized();

	virtual void SpudStoreCustomData(const USpudState* State, USpudStateCustomData* CustomData) {
		CustomData->WriteInt(Items.Num());

		for (auto entry : Items) {
			UItemInstance* item = entry.Value;
			item->store(this, State, CustomData);
		}
	}

	virtual void SpudRestoreCustomData(USpudState* State, USpudStateCustomData* CustomData) {
		clearInventory();
		int count = 0;
		bool b = CustomData->ReadInt(count);
		check(b);
		UWorld* w = GetWorld();
		for (int i = 0; i < count; i++) {
			TObjectPtr<UItemInstance> item = NewObject<UItemInstance>(w, UItemInstance::StaticClass());
			item->restore(this, State, CustomData);
		}
		
	}

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<const UItem*, UItemInstance*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	class ULoot* Loot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Money;

	FOnItemAddedSignature ItemAddedListeners;

	FOnItemRemovedSignature ItemRemovedListeners;

	FOnItemConsumedSignature ItemConsumedListeners;

	FOnClearInventorySignature ClearListeners;

	UFUNCTION(BlueprintCallable)
	virtual void addItem(UItemInstance* item);

	UFUNCTION(BlueprintCallable)
	UItemInstance* createItem(const UItem* itemType, int quantity) {
		UItemInstance* item = itemType->create(GetWorld(), quantity);
		addItem(item);
		return item;
	}

	UFUNCTION(BlueprintCallable)
	UItemInstance* removeInstance(UItemInstance* item) {
		return removeItem(item->ItemType, item->Count, false);
	}

	UFUNCTION(BlueprintCallable)
	UItemInstance* findItem(const UItem* type) {
		return Items.FindRef(type);
	}

	UFUNCTION(BlueprintCallable)
	class AItemActor* dropItem(const UItem* itemType, int quantity, AActor* target=nullptr) {
		UItemInstance* popped = removeItem(itemType, quantity, true);
		if (target == nullptr) {
			target = GetOwner();
		}
		return popped->spawn(target->GetWorld(), target->GetTransform());
	}
	UFUNCTION(BlueprintCallable)
	bool hasItem(const UItem* item, int minQuantity = 1) {
		UItemInstance* i = findItem(item);
		return i != nullptr && i->Count>=minQuantity;
	}
	UFUNCTION(BlueprintCallable)
	UItemInstance* transferItem(UInventory* otherInventory, const UItem* item, int quantity = 1) {
		UItemInstance* removed = removeItem(item, quantity, true);
		otherInventory->addItem(removed);
		return removed;
	}
	UFUNCTION(BlueprintCallable)
	UItemInstance* transferInstance(UInventory* otherInventory, UItemInstance* item, int quantity = 1) {
		return transferItem(otherInventory, item->ItemType, quantity);
	}
	UFUNCTION(BlueprintCallable)
	virtual UItemInstance* removeItem(const UItem* item, int quantity=1, bool spawnPopped=true, bool fireEvents=true);

	virtual void onItemCompleteRemoval(UItemInstance* item, bool fireEvents) {}

	UFUNCTION(BlueprintCallable)
	virtual UItemInstance* useItem(const UItem* item, int quantity);

	void RefreshItemInInventoryMenu(UItemInstance* item);

	virtual void clearInventory();
	virtual void resetInventory();
};
