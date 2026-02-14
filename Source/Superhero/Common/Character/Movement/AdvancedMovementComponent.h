// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MovementSpeed.h"
#include "AdvancedMovementComponent.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SUPERHERO_API UAdvancedMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WalkSpeed = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SlowWalkSpeed = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RunSpeed = 500;

	UPROPERTY(BlueprintReadOnly)
	EMovementSpeed MovementSpeed = EMovementSpeed::WALK;

	void TriggerStartSlowWalk(const FInputActionValue& Value)
	{
		StartSlowWalking();
	}
	void endSlowWalk()
	{
		StartWalking();
	}
	void TriggerEndSlowWalk(const FInputActionValue& Value)
	{
		StartWalking();
	}
	void ToggleSlowWalk(const FInputActionValue& Value)
	{
		ToggleSlowWalking();
	}
	void TriggerStartRun(const FInputActionValue& Value)
	{
		StartRunning();
	}
	void TriggerEndRun(const FInputActionValue& Value) {
		StartWalking();
	}
	inline bool IsRunning() const {
		return MovementSpeed == EMovementSpeed::RUN;
	}
	inline void StartRunning() {
		if (CanStartRunning()) {
			MovementSpeed = EMovementSpeed::RUN;
			MaxWalkSpeed = RunSpeed;
		}
	}
	inline bool IsSlowWalking() {
		return MovementSpeed == EMovementSpeed::SLOW_WALK;
	}
	inline void StartSlowWalking() {
		MovementSpeed = EMovementSpeed::SLOW_WALK;
		MaxWalkSpeed = SlowWalkSpeed;
	}

	void ToggleSlowWalking()
	{
		if (IsSlowWalking()) {
			StartWalking();
		}
		else {
			StartSlowWalking();
		}
	}
	
	inline void StartWalking() {
		MovementSpeed = EMovementSpeed::WALK;
		MaxWalkSpeed = WalkSpeed;
	}

	inline bool CanStartRunning() {
		return true;
	}


};
