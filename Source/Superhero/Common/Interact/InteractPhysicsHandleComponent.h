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

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	double physicshandleDistance = -1;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* InteractedActor;
public:

	/** Called for interaction input */
	void InteractTriggered() {
		if (InteractedActor != nullptr && InteractedActor->Implements<UInteractable>()) {
			IInteractable::Execute_Interact(InteractedActor, GetOwner());
		}
	}

	void InteractStart(FHitResult OutHit) {
		InteractedActor = OutHit.GetActor();
		auto h = OutHit.GetHitObjectHandle();
		auto c = OutHit.GetComponent();
		physicshandleDistance = OutHit.Distance;
		GrabComponentAtLocationWithRotation(c, "", h.GetLocation(), h.GetRotation());
	}

	void InteractEnd() {
		InteractedActor = nullptr;
		ReleaseComponent();
		physicshandleDistance = -1;
	}
};
