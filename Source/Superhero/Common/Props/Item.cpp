// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Actor/ItemActorStatic.h"
#include "Actor/ItemActorSkeletal.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"

UItemInstance * UItem::create(UObject* outer, int count) const
{
	UItemInstance * p = NewObject<UItemInstance>(outer, UItemInstance::StaticClass());
	p->ItemType = this;
	p->Count = count;
	//p->Durability = Durability;
	return p;
}

void UItem::sample(UInventory* inv, int count)
{
	if (count > 0) {
		inv->addItem(create(inv->GetWorld(), count));
	}
}

AItemActor* UItem::spawn(UWorld* world, class UItemInstance* instance, FTransform trans) const {
	if (isSkeletal()) {
		return AItemActorSkeletal::spawn(world, instance, trans);
	}else{
		return AItemActorStatic::spawn(world, instance, trans);
	}
}
