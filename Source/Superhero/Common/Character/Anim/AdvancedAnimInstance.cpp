// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedAnimInstance.h"
#include <Common/Inventory/ClothingSystem.h>
#include "GameFramework/Character.h"
#include <Common/Character/Movement/AdvancedMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>


void UAdvancedAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);
	if (IsValid(AdvancedMovement)) {
		
		IsLeftLegInFront = AdvancedMovement->IsLeftLegInFront;
		IsAiming = AdvancedMovement->IsAiming;
		if (IsAiming) {
			FRotator aimRot = Character->GetBaseAimRotation();
			FRotator actorRot = Character->GetActorRotation();
			FRotator aimDelta = UKismetMathLibrary::NormalizedDeltaRotator(aimRot, actorRot);
			AimPitch = aimDelta.Pitch;
			AimYaw = aimDelta.Yaw;
		}
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
