// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include <Common/Character/Movement/AdvancedMovementComponent.h>

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UAdvancedMovementComponent>(CharacterMovementComponentName)) {

	ClothingSys = CreateDefaultSubobject<UClothingSystem>(TEXT("Inventory"));
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