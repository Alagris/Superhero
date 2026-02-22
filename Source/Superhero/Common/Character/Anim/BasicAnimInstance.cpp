// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Character/Anim/BasicAnimInstance.h"
#include "GameFramework/Character.h"
#include "KismetAnimationLibrary.h"
#include <GameFramework/CharacterMovementComponent.h>



void UBasicAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaTime)
{
	if (IsValid(Character)) {
		UCharacterMovementComponent* mov = Character->GetCharacterMovement();
		Velocity = mov->Velocity;
		if (mov->IsSwimming()) {
			GroundSpeed = Velocity.Length();
		}
		else {
			GroundSpeed = FVector2d(Velocity).Length();
		}
		const FVector acc = mov->GetCurrentAcceleration();
		ShouldMove = acc != FVector(0, 0, 0) && GroundSpeed > ShouldMoveSpeedThreshold;
		const FRotator rot = Character->GetActorRotation();
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, rot);
		IsCrouching = mov->IsCrouching();
		IsSwimming = mov->IsSwimming();
		IsFalling = mov->IsFalling();
		IsStrafe = mov->bOrientRotationToMovement;
	}
	
}

void UBasicAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<ACharacter>(GetOwningActor());
}
