// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "MovementSpeed.h"
#include "AdvancedMovementComponent.generated.h"

struct FInputActionValue;
class UItemInstance;



/**
 * 
 */
UCLASS()
class SUPERHERO_API UAdvancedMovementComponent : public UBasicCharacterMovementComponent
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

	UPROPERTY(BlueprintReadOnly)
	bool IsLeftLegInFront;

	UPROPERTY(BlueprintReadOnly)
	bool IsAiming=false;


	void startAiming() {
		IsAiming = true;
		MaxWalkSpeed = SlowWalkSpeed;
	}

	void endAiming() {
		IsAiming = false;
		ResetSpeed();
	}



	inline bool IsPlayingAnimMontage(class UAnimMontage* AnimMontage) {
		return getAnimInstance()->Montage_IsPlaying(AnimMontage);
	}
	inline float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1) {
		return getAnimInstance()->Montage_Play(AnimMontage, InPlayRate);
	}
	inline void StopAnimMontage(float InBlendOutTime, const UAnimMontage* Montage = 0) {
		getAnimInstance()->Montage_Stop(InBlendOutTime, Montage);
	}
	inline UAnimInstance* getAnimInstance() const {
		return GetCharacterOwner()->GetMesh()->GetAnimInstance();
	}

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
	inline void ResetSpeed() {
		switch (MovementSpeed) {
		case EMovementSpeed::RUN:
			MaxWalkSpeed = RunSpeed;
			break;
		case EMovementSpeed::SLOW_WALK:
			MaxWalkSpeed = SlowWalkSpeed;
			break;
		case EMovementSpeed::WALK:
			MaxWalkSpeed = WalkSpeed;
			break;
		}
		
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
		if (!IsAiming) {
			MaxWalkSpeed = WalkSpeed;
		}
	}

	inline bool CanStartRunning() {
		return !IsAiming;
	}

	virtual void BeginPlay() override;
};
