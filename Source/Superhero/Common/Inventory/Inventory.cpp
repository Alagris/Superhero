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

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::addItem(UItem* item, int quantity)
{
	if (quantity > 0) {
		FItemInstance i;
		i.Count = 0;
		i.ItemType = item;
		FItemInstance& j = Items.FindOrAdd(item, i);
		j.Count += quantity;
		ItemAddedListeners.Broadcast(j, this);
	}
}

void UInventory::removeItem(UItem* item, int quantity)
{
	if (quantity > 0) {
		FSetElementId id = Items.FindId(item);
		TPair<UItem*, FItemInstance>& i = Items.Get(id);
		i.Value.Count -= quantity;
		ItemRemovedListeners.Broadcast(i.Value, this);
		if (i.Value.Count <= 0) {
			Items.Remove(id);
		}
	}
}

void UInventory::useItem(UItem* item, int quantity)
{
	if (quantity > 0) {
		FSetElementId id = Items.FindId(item);
		TPair<UItem*, FItemInstance>& i = Items.Get(id);
		item->use(this, i.Value);
		if (i.Value.Count <= 0) {
			Items.Remove(id);
		}
	}
}

