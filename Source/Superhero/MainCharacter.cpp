// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include <Common/Character/Movement/AdvancedMovementComponent.h>

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UAdvancedMovementComponent>(CharacterMovementComponentName)) {

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	ClothingSys = CreateDefaultSubobject<UClothingSystem>(TEXT("Clothing"));
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

}


void AMainCharacter::OnDialogueEntered_Implementation(APlayerController* Player)
{
}

void AMainCharacter::OnDialogueExited_Implementation(APlayerController* Player)
{
}

void AMainCharacter::OnPlayDialogueAnim_Implementation(UAnimMontage* Anim)
{
}