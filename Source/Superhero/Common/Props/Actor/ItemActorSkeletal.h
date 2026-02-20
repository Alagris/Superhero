// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "Common/Inventory/ItemInstance.h"
#include "ItemActorSkeletal.generated.h"


UCLASS()
class SUPERHERO_API AItemActorSkeletal : public AItemActor
{
	GENERATED_BODY()
	

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent * Mesh;


public:	
	// Sets default values for this actor's properties
	AItemActorSkeletal();

	inline USkeletalMeshComponent* getMeshComponent() {
		return Mesh;
	}
	virtual bool isSkeletal() const override {
		return true;
	}

	virtual void setItem(UItemInstance * item) override{
		Super::setItem(item);
		if (item) {
			//check(item->isSkeletal());
			Mesh->SetSkeletalMesh(item->getSkeletalMesh());
			item->applyMaterials(Mesh);
		}
		
	}

	static AItemActorSkeletal* spawn(UWorld * world, UItemInstance* item, FTransform trans) {
		AItemActorSkeletal* a = world->SpawnActor<AItemActorSkeletal>(AItemActorSkeletal::StaticClass(), trans);
		a->setItem(item);
		return a;
	}

};
