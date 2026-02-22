// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_NextAttackReady.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Common/Character/Movement/AdvancedMovementComponent.h>

void UAnimNotify_NextAttackReady::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if (ACharacter* p = Cast<ACharacter>(MeshComp->GetOwner())) {
		UCharacterMovementComponent* mov = p->GetCharacterMovement();
		if (UAdvancedMovementComponent* aMov = Cast<UAdvancedMovementComponent>(mov)) {
			aMov->OnNextAttackReady();
		}
	}
}