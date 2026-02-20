// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "Common/Inventory/Inventory.h"
// Sets default values
AItemActor::AItemActor()
{
	this->SetActorHiddenInGame(true);
	PrimaryActorTick.bCanEverTick = false;

}

void AItemActor::OnInteract_Implementation(AActor* actor, UItemInstance* item, const FHitResult& Hit)
{
	UInventory* inv = actor->GetComponentByClass<UInventory>();
	if (inv) {
		inv->addItem(Item);
		Item = nullptr;
		Destroy();
	}
}
