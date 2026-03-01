// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ShootProjectile.h"
#include "Common/Combat/CombatComponent.h"

void UAnimNotify_ShootProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	if(IsValid(Projectile)){
		AActor* target=nullptr;
		if (UCombatComponent* combat = MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>()) {
			target = combat->AutoAimTarget;
		}
		Projectile->shootFromSkeletalSocket(CharacterSocket, MeshComp, nullptr, target);
	}
}
