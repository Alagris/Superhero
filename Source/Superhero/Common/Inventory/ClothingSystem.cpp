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
		inventory = c->FindComponentByClass<UInventory>();
		if (IsValid(inventory)) {
			CharacterMesh = c->GetMesh();
			inventory->ItemEquippedListeners.AddUObject(this, &UClothingSystem::OnEquip);
			inventory->ItemUnequippedListeners.AddUObject(this, &UClothingSystem::OnUnequip);
			for (auto e:inventory->Items) {
				if (e.Value.EquippedAt >= 0) {
					e.Value.EquippedAt = -1;
					e.Key->use(inventory, e.Value);
				}
			}
		}
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

void UClothingSystem::OnEquip(UClothingItem* type, FItemInstance& item, UInventory* inv)
{
	
	if (item.EquippedAt == -1) {
		uint8 s8 = type->slot();
		if ((OccupiedDeviousClothingSlots & s8) == 0) {
			if ((OccupiedClothingSlots & s8) != 0) {
				for (int i = 0; i < ClothesMeshes.Num();i++) {
					if ((ClothesMeshes[i].Item->slot() & s8) != 0) {
						FItemInstance&j = inventory->Items[ClothesMeshes[i].Item];
						RemoveItem(ClothesMeshes[i].Item, j);
					}
				}
			}
			if (USkeletalMesh* clothingMesh = type->WearableMesh.LoadSynchronous()) {
				USkeletalMeshComponent* clothingComp = createSkeletalMeshComponent(clothingMesh);
				item.EquippedAt = ClothesMeshes.Add(FEquippedClothes(clothingComp, type));
				OccupiedClothingSlots |= s8;
				if (type->IsDevious) OccupiedDeviousClothingSlots |= s8;
			}
		}
	}
}

void UClothingSystem::OnUnequip(UClothingItem* type, FItemInstance& item, UInventory* inv)
{
	if (!type->IsDevious) {
		RemoveItem(type, item);
	}
}

void UClothingSystem::RemoveItem(UClothingItem* type, FItemInstance& item)
{
	if (item.EquippedAt >= 0) {
		destroySkeletalMeshComponent(ClothesMeshes[item.EquippedAt].Mesh);
		ClothesMeshes.RemoveAtSwap(item.EquippedAt);
		item.EquippedAt = -1;
		OccupiedClothingSlots &= ~type->slot();
	}
}

