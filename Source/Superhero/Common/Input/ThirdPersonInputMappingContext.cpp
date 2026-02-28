// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonInputMappingContext.h"
#include "Common/Character/ThirdPerson/ThirdPersonCharacter.h"
#include <EnhancedInputComponent.h>
#include <Common/Combat/CombatComponent.h>
#include <Common/Character/Movement/AdvancedMovementComponent.h>
#include <Common/Inventory/ClothingSystem.h>



void UThirdPersonInputMappingContext::BindToThirdPerson(UEnhancedInputComponent* EnhancedInputComponent, AThirdPersonCharacter* a)
{
	
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, a, &AThirdPersonCharacter::TriggerJumpStart);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, a, &AThirdPersonCharacter::TriggerJumpEnd);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, a, &AThirdPersonCharacter::TriggerMove);
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, a, &AThirdPersonCharacter::TriggerCameraZoom);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, a, &AThirdPersonCharacter::TriggerInteract);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, a, &AThirdPersonCharacter::TriggerInteractStart);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, a, &AThirdPersonCharacter::TriggerInteractEnd);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Canceled, a, &AThirdPersonCharacter::TriggerInteractEnd);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, a, &AThirdPersonCharacter::TriggerCrouch);
	
	
	if (UAdvancedMovementComponent* m = Cast<UAdvancedMovementComponent>(a->GetCharacterMovement())) {
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, m, &UAdvancedMovementComponent::TriggerStartRun);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, m, &UAdvancedMovementComponent::TriggerEndRun);
		EnhancedInputComponent->BindAction(SlowWalkAction, ETriggerEvent::Started, m, &UAdvancedMovementComponent::ToggleSlowWalk);
	}
	if (UCombatComponent* m = a->GetComponentByClass<UCombatComponent>()) {
		EnhancedInputComponent->BindAction(AttackLeftAction, ETriggerEvent::Started, m, &UCombatComponent::TriggerLeftAttackStart);
		EnhancedInputComponent->BindAction(AttackLeftAction, ETriggerEvent::Completed, m, &UCombatComponent::TriggerLeftAttackEnd);
		EnhancedInputComponent->BindAction(AttackRightAction, ETriggerEvent::Started, m, &UCombatComponent::TriggerRightAttackStart);
		EnhancedInputComponent->BindAction(AttackRightAction, ETriggerEvent::Completed, m, &UCombatComponent::TriggerRightAttackEnd);
	}
	
}
