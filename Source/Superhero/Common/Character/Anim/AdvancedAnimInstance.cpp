// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedAnimInstance.h"
#include <Common/Inventory/ClothingSystem.h>
#include "GameFramework/Character.h"
#include <Common/Character/Movement/AdvancedMovementComponent.h>


void UAdvancedAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);
	if (IsValid(AdvancedMovement)) {
		IsLeftLegInFront = AdvancedMovement->IsLeftLegInFront;
	}
	if (IsValid(Equipment)) {
		LocomotionStyleL = Equipment->HandL.LocomotionStyle;
		LocomotionStyleR = Equipment->HandR.LocomotionStyle;
	}
}

void UAdvancedAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (IsValid(Character)) {
		UCharacterMovementComponent* mov = Character->GetCharacterMovement();
		AdvancedMovement = Cast<UAdvancedMovementComponent>(mov);
		if (UClothingSystem* c = GetOwningActor()->GetComponentByClass<UClothingSystem>()) {
			Equipment = c;
		}
	}
}
