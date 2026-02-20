// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/Inventory.h"
#include "Common/UI/Inventory/InventoryMenu.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();
	EnsureLootInitialized();
}

bool UInventory::EnsureLootInitialized()
{
	if (!isLootInitialized) {
		resetInventory();
		isLootInitialized = true;
		return true;
	}
	return false;
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInventory::addItem(UItemInstance* item)
{
	if (item->Count > 0) {
		UItemInstance * val = Items.FindOrAdd(item->ItemType, item);
		check(val != nullptr);
		if (val == item) {
			item->Owner = this;
			val = item;
			if (IsValid(InventoryWidget)) {
				InventoryWidget->addItem(val);
			}
		}
		else {
			val->Count += item->Count;
			RefreshItemInInventoryMenu(val);
		}
		ItemAddedListeners.Broadcast(val, this);
	}
}


UItemInstance* UInventory::removeItem(const UItem* item, int quantity, bool spawnPopped, bool fireEvents)
{
	if (quantity > 0) {
		FSetElementId id = Items.FindId(item);
		if (id.IsValidId()) {
			TPair<const UItem*, UItemInstance*>& i = Items.Get(id);
			UItemInstance* popped = i.Value->popCount(GetWorld(), quantity, spawnPopped);
			if (popped == i.Value) {
				Items.Remove(id);
				popped->Owner = nullptr;
				onItemCompleteRemoval(popped, fireEvents);
				if (fireEvents) {
					ItemRemovedListeners.Broadcast(i.Value, this);
				}
				if (IsValid(InventoryWidget)) {
					InventoryWidget->removeItem(i.Value);
				}
			}
			else {
				RefreshItemInInventoryMenu(i.Value);
			}
			
			return popped;
		}
	}
	return nullptr;
}

UItemInstance* UInventory::useItem(const UItem* item, int quantity)
{
	if (quantity > 0) {
		FSetElementId id = Items.FindId(item);
		if (id.IsValidId()) {
			TPair<const UItem*, UItemInstance*>& i = Items.Get(id);
			i.Value->use(GetOwner());
			if (i.Value->Count <= 0) {
				Items.Remove(id);
			}
			return i.Value;
		}
	}
	return nullptr;
}

void UInventory::RefreshItemInInventoryMenu(UItemInstance* item)
{
	if (IsValid(InventoryWidget)) {
		InventoryWidget->updateItem(item);
	}
}

void UInventory::clearInventory()
{
	if (IsValid(InventoryWidget)) {
		InventoryWidget->clearItems();
	}
	ClearListeners.Broadcast(this);
	Items.Empty();
}

void UInventory::resetInventory()
{
	clearInventory();
	if (IsValid(Loot)) {
		Loot->sample(this, 1);
		if (IsValid(InventoryWidget)) {
			InventoryWidget->addAllItems();
		}
	}
}

