// Fill out your copyright notice in the Description page of Project Settings.


#include "FactionsComponent.h"
#include "CombatComponent.h"
#include "Common/Inventory/Health.h"
#include "Common/Inventory/Inventory.h"


// Sets default values for this component's properties
UFactionsComponent::UFactionsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UFactionsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UFactionsComponent::InitializeComponent()
{
	Super::InitializeComponent();

	
	ClothingComponent = GetOwner()->GetComponentByClass<UClothingSystem>();

	HealthComponent = GetOwner()->GetComponentByClass<UHealth>();
	
	InventoryComponent = GetOwner()->GetComponentByClass<UInventory>();

	TeamId = IsValid(Faction) ? Faction->TeamId : FGenericTeamId::NoTeam;
}

// Called every frame
void UFactionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

