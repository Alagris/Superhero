// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraGunItem.h"
#include "NiagaraFunctionLibrary.h"
#include "Common/Inventory/Inventory.h"
#include "Common/Inventory/ItemInstance.h"
#include "NiagaraComponent.h"
#include <Common/Inventory/ClothingSystem.h>

void UNiagaraGunItem::attackTrigger(UItemInstance* instance, bool isHeavy) const
{
	if (IsValid(instance->SceneComp)){
		FTransform t;
		if (UStaticMeshComponent * sta= Cast<UStaticMeshComponent>(instance->SceneComp)) {
			t = sta->GetSocketTransform(BarrelTipSocket);
		}else if (USkeletalMeshComponent* skel = Cast<USkeletalMeshComponent>(instance->SceneComp)) {
			t = skel->GetSocketTransform(BarrelTipSocket);
		}
		else {
			return;
		}

		
		UNiagaraComponent* n = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			instance->Owner->GetWorld(),
			Niagara,
			t.GetLocation(),
			t.GetRotation().Rotator()
		);
		for (const FUserParam & p : UserParams) {
			n->SetVectorParameter(p.Name, p.Value);
		}
	}	
}
