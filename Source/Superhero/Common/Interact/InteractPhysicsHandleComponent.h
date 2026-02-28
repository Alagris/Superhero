// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Interactable.h"
#include "InteractPhysicsHandleComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UInteractPhysicsHandleComponent : public UPhysicsHandleComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	double physicshandleDistance = -1;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* InteractedActor;

	UPROPERTY()
	FHitResult HitResult;

	/** Called for interaction input */
	void InteractTriggered(class UItemInstance * item=nullptr) {
		if (InteractedActor != nullptr && InteractedActor->Implements<UInteractable>()) {
			IInteractable::Execute_OnInteract(InteractedActor, GetOwner(), item, HitResult);
		}
	}

	void InteractStart() {
		InteractedActor = HitResult.GetActor();
		FActorInstanceHandle h = HitResult.GetHitObjectHandle();
		UPrimitiveComponent * c = HitResult.GetComponent();
		physicshandleDistance = HitResult.Distance;
		FVector loc = HitResult.Location;
		FRotator rot = c->GetComponentRotation();
		GrabComponentAtLocationWithRotation(c, "", loc, rot);
	}

	void InteractEnd() {
		InteractedActor = nullptr;
		ReleaseComponent();
		physicshandleDistance = -1;
	}
};
