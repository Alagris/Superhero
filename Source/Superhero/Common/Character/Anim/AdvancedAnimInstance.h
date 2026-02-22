// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Character/Anim/BasicAnimInstance.h"
#include "AdvancedAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UAdvancedAnimInstance : public UBasicAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsLeftLegInFront;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsAiming;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float AimPitch;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float AimYaw;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	int LocomotionStyleL;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	int	LocomotionStyleR;

	class UAdvancedMovementComponent* AdvancedMovement;

	class UClothingSystem* Equipment;
};
