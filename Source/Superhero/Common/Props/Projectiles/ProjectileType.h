// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameFramework/Character.h"
#include "Common/Inventory/ItemInstance.h"
#include "Common/Inventory/Inventory.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include "ProjectileType.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UProjectileType : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ProjectileGravity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector ProjectileVelocity = FVector(6000, 0, 0);

	void playFireSound(const UObject * worldObject, FTransform& trans) const{
		if (IsValid(FireSound)) {
			FVector loc = trans.GetLocation();
			UGameplayStatics::PlaySoundAtLocation(worldObject, FireSound, loc);
		}
	}
	AActor* shootFromItemSocket(FName itemSocket, UItemInstance* instance, AActor* autoAimTarget = nullptr) const{
		FTransform t;
		if (itemSocket.IsValid()) {

			if (!instance->getSocketTransform(itemSocket, t)) {
				return nullptr;
			}
		}
		else if (UInventory* owner = instance->Owner) {
			t = owner->GetOwner()->GetActorTransform();
		}
		
		return shootProjectileAutoAim(instance->getActorOwner(), instance, t, autoAimTarget);
	}
	AActor* shootFromCharacterSocket(FName itemSocket, ACharacter* character, class UItemInstance* instance, AActor* autoAimTarget = nullptr) const {
		FTransform t = character->GetMesh()->GetSocketTransform(itemSocket);
		return shootProjectileAutoAim(character, instance, t, autoAimTarget);
	}
	AActor* shootProjectileFromItem(class UItemInstance* instance, FTransform& trans, AActor* autoAimTarget = nullptr) const {
		return shootProjectileAutoAim(instance->getActorOwner(), instance, trans, autoAimTarget);
	}
	AActor* shootFromSkeletalSocket(FName socket, USkeletalMeshComponent * meshComp, class UItemInstance* instance, AActor* autoAimTarget = nullptr) const {
		FTransform t = meshComp->GetSocketTransform(socket);
		return shootProjectileAutoAim(meshComp->GetOwner(), instance, t, autoAimTarget);
	}
	AActor* shootProjectileAutoAim(AActor* shooter, class UItemInstance* instance, FTransform& trans, AActor* autoAimTarget = nullptr) const {
		if (IsValid(autoAimTarget)) {
			FVector start = trans.GetLocation();
			FVector end = autoAimTarget->GetActorLocation();
			FRotator rot = UKismetMathLibrary::FindLookAtRotation(start, end);
			trans.SetRotation(rot.Quaternion());
		}
		return shootProjectile(shooter, instance, trans);
	}
	virtual AActor* shootProjectile(AActor* shooter, class UItemInstance* instance, FTransform& trans) const;
};
