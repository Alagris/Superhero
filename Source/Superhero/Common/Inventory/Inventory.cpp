// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/Inventory.h"

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
		}
		else {
			val->Count += item->Count;
		}
		ItemAddedListeners.Broadcast(val, this);
	}
}

UItemInstance* UInventory::spawnItem(const UItem* itemType, int quantity)
{
	UItemInstance* item = itemType->spawn(GetWorld(), quantity);
	addItem(item);
	return item;
}

UItemInstance* UInventory::removeItem(UItemInstance* item) {
	
	FSetElementId id = Items.FindId(item->ItemType);
	if (id.IsValidId()) {
		TPair<const UItem*, UItemInstance*>& i = Items.Get(id);
		if (item == i.Value) {
			Items.Remove(id);
			item->Owner = nullptr;
			ItemRemovedListeners.Broadcast(item, this);
		}
	}
	return item;
}
UItemInstance* UInventory::removeItem(const UItem* item, int quantity, bool spawnPopped)
{
	if (quantity > 0) {
		FSetElementId id = Items.FindId(item);
		if (id.IsValidId()) {
			TPair<const UItem*, UItemInstance*>& i = Items.Get(id);
			UItemInstance* popped = i.Value->popCount(GetWorld(), quantity, spawnPopped);
			if (popped == i.Value) {
				Items.Remove(id);
				popped->Owner = nullptr;
				ItemRemovedListeners.Broadcast(i.Value, this);
				
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

void UInventory::clearInventory()
{
	ClearListeners.Broadcast(this);
	Items.Empty();
}

void UInventory::resetInventory()
{
	clearInventory();
	if (IsValid(Loot)) {
		Loot->sample(this, 1);
	}
}

