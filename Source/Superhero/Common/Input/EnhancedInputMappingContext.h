// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "EnhancedInputMappingContext.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UEnhancedInputMappingContext : public UInputMappingContext
{
	GENERATED_BODY()
public:

	UInputAction* mapKey(UObject* Outer,FKey key, EInputActionValueType type = EInputActionValueType::Boolean, bool triggerWhenPaused = false);
	UInputAction* map2Keys(UObject* Outer, FKey key, FKey key2, EInputActionValueType type = EInputActionValueType::Boolean, bool triggerWhenPaused = false);
	UInputAction* mapTapKey(UObject* Outer,FKey key, float timeThreshold);
	UInputAction* mapPressKey(UObject* Outer, FKey key, bool triggerWhenPaused = false);
	UInputAction* mapTapOrHoldKey(UObject* Outer,FKey key, float timeThreshold);
	UInputAction* mapHoldThenOngoingKey(UObject* Outer,FKey key, float timeThreshold);
	UInputAction* mapHoldKey(UObject* Outer,FKey key, float timeThreshold);
	UInputAction* moveKeys(UObject* Outer);
	UInputAction* lookKeys(UObject* Outer);

	UInputAction* makeSlowWalkAction(UObject* Outer) { return mapKey(Outer,EKeys::V); }
	UInputAction* makeRunAction(UObject* Outer) { return mapKey(Outer,EKeys::LeftShift); }
	UInputAction* makeJumpAction(UObject* Outer) { return mapKey(Outer,EKeys::SpaceBar); }
	UInputAction* makeLeftHandedLightAttackAction(UObject* Outer,float timeThreshold) { return mapTapKey(Outer,EKeys::LeftMouseButton, timeThreshold); }
	UInputAction* makeRightHandedLightAttackAction(UObject* Outer,float timeThreshold) { return mapTapKey(Outer,EKeys::RightMouseButton, timeThreshold); }
	UInputAction* makeLeftHandedHeavyAttackAction(UObject* Outer,float timeThreshold) { return mapHoldThenOngoingKey(Outer,EKeys::LeftMouseButton, timeThreshold); }
	UInputAction* makeRightHandedHeavyAttackAction(UObject* Outer,float timeThreshold) { return mapHoldThenOngoingKey(Outer,EKeys::RightMouseButton, timeThreshold); }
	UInputAction* makeAttackCancelAction(UObject* Outer) { return mapKey(Outer,EKeys::R); }
	UInputAction* makeInteractAction(UObject* Outer) { return mapTapOrHoldKey(Outer,EKeys::E, 0.5); }
	UInputAction* makeLockAction(UObject* Outer) { return mapKey(Outer,EKeys::MiddleMouseButton); }
	UInputAction* makeZoomAction(UObject* Outer) { return mapKey(Outer,EKeys::MouseWheelAxis, EInputActionValueType::Axis1D); }
	UInputAction* makeCrouchAction(UObject* Outer) { return mapKey(Outer,EKeys::LeftControl); }
	UInputAction* makePauseGameAction(UObject* Outer) { return mapKey(Outer,EKeys::Escape, EInputActionValueType::Boolean, true); }
	UInputAction* makeOpenInvAction(UObject* Outer) { return mapKey(Outer, EKeys::C, EInputActionValueType::Boolean, true); }
	void mapKey(UInputAction* act, FKey key, bool negateX, bool negateY, bool negateZ);
	void mapKey(UInputAction* act, FKey key, bool negate = false, bool swizzle = false, EInputAxisSwizzle order = EInputAxisSwizzle::YXZ);
	virtual void initialize(APlayerController* c) {};
	virtual void setMapping(APlayerController* c);

	

	
};
