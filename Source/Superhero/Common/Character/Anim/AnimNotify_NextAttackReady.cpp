// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_NextAttackReady.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Common/Character/Movement/AdvancedMovementComponent.h>
#include <Common/Combat/CombatComponent.h>

void UAnimNotify_NextAttackReady::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if (UCombatComponent* combat = MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>()) {
		combat->OnNextAttackReady();
	}
}