// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedMovementComponent.h"
#include "Common/Inventory/ItemInstance.h"

void UAdvancedMovementComponent::ExecuteNextAttack(bool isHeavy)
{
	if (WantsToAttack != nullptr) {
		LastPlayerAttackName = WantsToAttack->getNextAttackAnimMontage(AttackState, isHeavy);
		FCharacterAnim * a = AnimationCollection.Find(LastPlayerAttackName);
		if (a != nullptr) {
			LastPlayerAttackMontage = a->Anim.LoadSynchronous();
			if (IsValid(LastPlayerAttackMontage)) {
				CanPlayNextAttack = false;
				PlayAnimMontage(LastPlayerAttackMontage);
			}
		}

	}
}
