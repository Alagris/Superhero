// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ISpudObject.h"
#include "Common/Interact/Interactable.h"
#include "Bed.generated.h"

UCLASS()
class SUPERHERO_API ABed : public AActor, public ISpudObject, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation(AActor* actor, class UItemInstance* item, const struct FHitResult& Hit) override {
		
	}
};
