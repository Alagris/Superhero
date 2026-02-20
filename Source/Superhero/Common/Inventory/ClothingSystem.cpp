// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/ClothingSystem.h"
#include "GameFramework/Character.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"
#include "Common/Props/ClothingItem.h"




void UClothingSystem::InitializeComponent()
{
	Super::InitializeComponent();
	if (ACharacter* c = Cast<ACharacter>(GetOwner())) {
		CharacterMesh = c->GetMesh();
	}
}

// Called when the game starts
void UClothingSystem::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}


// Called every frame
void UClothingSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClothingSystem::destroySkeletalMeshComponent(USkeletalMeshComponent* comp)
{
	if (IsValid(comp)) {
		/*
		int childCount = comp->GetNumChildrenComponents();
		for (int i = 0; i < childCount; i++) {
			if (USkeletalMeshComponent* child = Cast< USkeletalMeshComponent>(comp->GetChildComponent(i))) {
				destroySkeletalMeshComponent(child);
			}
		}
		*/
		comp->UnregisterComponent();
	}
}

USkeletalMeshComponent* UClothingSystem::createSkeletalMeshComponent(USkeletalMesh* mesh)
{
	USkeletalMeshComponent* clothingComp = NewObject<USkeletalMeshComponent>(this, USkeletalMeshComponent::StaticClass());
	clothingComp->RegisterComponent();
	clothingComp->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	clothingComp->SetSkeletalMesh(mesh);
	clothingComp->SetAnimInstanceClass(CharacterMesh->AnimClass);
	clothingComp->SetLeaderPoseComponent(CharacterMesh, true);
	return clothingComp;
}

void UClothingSystem::UnequipAll(bool fireEvents)
{
	OccupiedDeviousClothingSlots = 0;
	OccupiedClothingSlots = 0;
	for (int i = 0; i < ClothesMeshes.Num(); i++) {
		const UClothingItem* t = ClothesMeshes[i].ItemType;
		UItemInstance* j = ClothesMeshes[i].Item;
		destroySkeletalMeshComponent(ClothesMeshes[i].Mesh);
		j->EquippedAt = -1;
		RefreshItemInInventoryMenu(j);
		if (fireEvents) {
			ItemUnequippedListeners.Broadcast(t, j, this);
		}
		
	}
	ClothesMeshes.Empty();
}

void UClothingSystem::Equip(const UClothingItem* type, UItemInstance* item, bool fireEvents)
{
	
	if (item->EquippedAt == -1) {
		uint8 s8 = type->slot();
		if ((OccupiedDeviousClothingSlots & s8) == 0) {
			if ((OccupiedClothingSlots & s8) != 0) {
				for (int i = 0; i < ClothesMeshes.Num();i++) {
					if ((ClothesMeshes[i].ItemType->slot() & s8) != 0) {
						UItemInstance*j = ClothesMeshes[i].Item;
						RemoveClothingMesh(j, fireEvents);
					}
				}
			}
			if (USkeletalMesh* clothingMesh = type->WearableMesh.LoadSynchronous()) {
				USkeletalMeshComponent* clothingComp = createSkeletalMeshComponent(clothingMesh);
				item->EquippedAt = ClothesMeshes.Add(FEquippedClothes(clothingComp, type, item));
				OccupiedClothingSlots |= s8;
				if (type->IsDevious) OccupiedDeviousClothingSlots |= s8;
				RefreshItemInInventoryMenu(item);
				if (fireEvents) {
					ItemEquippedListeners.Broadcast(type, item, this);
				}
			}
		}
	}
}

void UClothingSystem::Unequip(const UClothingItem* type, UItemInstance* item, bool fireEvents)
{
	if (!type->IsDevious) {
		RemoveClothingMesh(item, fireEvents);
	}
}

void UClothingSystem::RemoveClothingMesh(UItemInstance* item, bool fireEvents)
{
	if (item->EquippedAt >= 0) {
		const int idx = item->EquippedAt;
		const UClothingItem * type = ClothesMeshes[idx].ItemType;
		destroySkeletalMeshComponent(ClothesMeshes[idx].Mesh);
		ClothesMeshes.Last().Item->EquippedAt = idx;
		ClothesMeshes.RemoveAtSwap(idx);
		item->EquippedAt = -1;
		OccupiedClothingSlots &= ~type->slot();
		RefreshItemInInventoryMenu(item);
		if (fireEvents ) {
			ItemUnequippedListeners.Broadcast(type, item, this);
		}
	}
}


void UClothingSystem::autoEquip()
{
	
	UnequipAll();
	for (auto& entry : Items) {
		UItemInstance* item = entry.Value;
		if (const UClothingItem* clothingItem = Cast<UClothingItem>(item->ItemType)) {
			if (!clothingItem->IsDevious && canEquipClothes(clothingItem)) {
				Equip(clothingItem, item);
			}
		}
	}
}