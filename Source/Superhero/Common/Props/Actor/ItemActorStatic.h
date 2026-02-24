// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "ItemActorStatic.generated.h"


UCLASS()
class SUPERHERO_API AItemActorStatic : public AItemActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Sets default values for this actor's properties
	AItemActorStatic();

	inline UStaticMeshComponent* getMeshComponent() {
		return Mesh;
	}
	virtual bool isSkeletal() const override {
		return false;
	}

	virtual bool isProjectile() const {
		return false;
	}
	virtual void setItem(UItemInstance* item) override{
		Super::setItem(item);
		if (item) {
			//check(!item->isSkeletal());
			Mesh->SetStaticMesh(item->getMesh());
			item->applyMaterials(Mesh);
			item->SceneComp = Mesh;
		}
	}

	static AItemActorStatic* spawn(UWorld * world, UItemInstance* item, FTransform trans) {
		TObjectPtr<AItemActorStatic> a = world->SpawnActor<AItemActorStatic>(AItemActorStatic::StaticClass(), trans);
		a->setItem(item);
		return a;
	}

};
