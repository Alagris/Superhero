// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyFrontLeg.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Common/Character/Movement/AdvancedMovementComponent.h>

void UNotifyFrontLeg::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if (ACharacter* p = Cast<ACharacter>(MeshComp->GetOwner())) {
		UCharacterMovementComponent* mov = p->GetCharacterMovement();
		if (UAdvancedMovementComponent* aMov = Cast<UAdvancedMovementComponent>(mov)) {
			aMov->IsLeftLegInFront = LeftLegIsInFront;
		}
	}
}