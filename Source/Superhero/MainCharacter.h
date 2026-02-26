// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Character/ThirdPerson/ThirdPersonCharacter.h"
#include "Common/Interact/Interactable.h"
#include <Common/Inventory/ClothingSystem.h>
#include <Common/Inventory/NameComponent.h>
#include <Common/Interact/Hittable.h>
#include <Common/Inventory/Health.h>
#include "MainCharacter.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API AMainCharacter : public AThirdPersonCharacter, public ISpudObject, public IHittable
{
	GENERATED_BODY()
public:
	AMainCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class UDialogueStage> DialogueStage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UClothingSystem* ClothingSys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UHealth* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UNameComponent* Dialogue;

	virtual void OnHit_Implementation(class AActor* projectile, AActor* shooter, class UItemInstance* rangedWeapon, float hitSpeed, FVector NormalImpulse, const FHitResult& Hit) {
		Health->ReceiveHit(projectile, shooter, rangedWeapon, hitSpeed, NormalImpulse, Hit);
	}

};
