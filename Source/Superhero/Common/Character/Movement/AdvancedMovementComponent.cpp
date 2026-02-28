// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedMovementComponent.h"
#include "Common/Inventory/ItemInstance.h"


void UAdvancedMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	StartWalking();
}
