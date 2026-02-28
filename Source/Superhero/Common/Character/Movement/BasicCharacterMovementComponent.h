// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BasicCharacterMovementComponent.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API UBasicCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:


	void setUseAccelerationForPathFollowing(bool use) {
		NavMovementProperties.bUseAccelerationForPaths = use;
	}
};
