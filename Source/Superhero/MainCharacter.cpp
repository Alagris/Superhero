// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include <Common/Inventory/NameComponent.h>
#include <Common/Character/Movement/AdvancedMovementComponent.h>

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UAdvancedMovementComponent>(CharacterMovementComponentName)) {

	ClothingSys = CreateDefaultSubobject<UClothingSystem>(TEXT("Inventory"));
	Health = CreateDefaultSubobject<UHealth>(TEXT("Health"));
	Dialogue = CreateDefaultSubobject<UNameComponent>(TEXT("Dialogue"));
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);



}