// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/Inventory/ItemInstance.h"
#include "Common/Interact/Interactable.h"
#include "ISpudObject.h"
#include "ItemActor.generated.h"


UCLASS()
class SUPERHERO_API AItemActor : public AActor, public IInteractable, public ISpudObject, public ISpudObjectCallback
{
	GENERATED_BODY()
	
	


public:	
	// Sets default values for this actor's properties
	AItemActor();

	// class APooledWorldManager* worldRef;
	UPROPERTY()
	FGuid SpudGuid;

	UPROPERTY(SaveGame)
	UItemInstance * Item;
	
	virtual ESpudRespawnMode GetSpudRespawnMode_Implementation() const override { return ESpudRespawnMode::AlwaysRespawn; }

	
	virtual void SpudPostRestore_Implementation(const USpudState* State) override{
		setItem(Item);
	}

	virtual bool isSkeletal() const{
		return false;
	}
	virtual void setItem(UItemInstance* item) {
		Item = item;
		SetEnabled(item != nullptr);
	}

	
	virtual void OnInteract_Implementation(AActor* actor, class UItemInstance* item, const struct FHitResult& Hit) override;
	
	inline bool isEnabled() const{
		return this->IsHidden();
	}
	inline void SetEnabled(bool enabled) {
		this->SetActorHiddenInGame(!enabled);
		this->SetActorEnableCollision(enabled);
	}
	
};
