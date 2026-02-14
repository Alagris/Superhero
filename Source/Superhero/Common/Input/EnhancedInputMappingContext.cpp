// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Input/EnhancedInputMappingContext.h"
#include "HoldThenOngoing.h"
#include "TapOrHold.h"
#include <EnhancedInputSubsystems.h>

UInputAction* UEnhancedInputMappingContext::mapKey(UObject* Outer, FKey key, EInputActionValueType type, bool triggerWhenPaused) {
	UInputAction* act = NewObject<UInputAction>(Outer);
	act->bTriggerWhenPaused = triggerWhenPaused;
	act->ValueType = type;
	MapKey(act, key);
	return act;
}
UInputAction* UEnhancedInputMappingContext::mapTapOrHoldKey(UObject* Outer, FKey key, float timeThreshold) {
	UInputAction* act = NewObject<UInputAction>(Outer);
	FEnhancedActionKeyMapping& mapping = MapKey(act, key);
	UTapOrHold* tap = NewObject<UTapOrHold>(Outer);
	tap->TapReleaseTimeThreshold = timeThreshold;
	mapping.Triggers.Add(tap);
	return act;
}

UInputAction* UEnhancedInputMappingContext::mapHoldThenOngoingKey(UObject* Outer, FKey key, float timeThreshold)
{

	UInputAction* act = NewObject<UInputAction>(Outer);
	FEnhancedActionKeyMapping& mapping = MapKey(act, key);
	UHoldThenOngoing* tap = NewObject<UHoldThenOngoing>(Outer);
	tap->HoldTimeThreshold = timeThreshold;
	mapping.Triggers.Add(tap);
	return act;
}

UInputAction* UEnhancedInputMappingContext::mapHoldKey(UObject* Outer,FKey key, float timeThreshold) {
	UInputAction* act = NewObject<UInputAction>(Outer);
	FEnhancedActionKeyMapping& mapping = MapKey(act, key);
	UInputTriggerHold* hold = NewObject<UInputTriggerHold>(Outer);
	hold->HoldTimeThreshold = timeThreshold;
	mapping.Triggers.Add(hold);
	return act;
}

UInputAction* UEnhancedInputMappingContext::moveKeys(UObject * Outer)
{
	UInputAction* MoveAction = NewObject<UInputAction>(Outer);
	MoveAction->ValueType = EInputActionValueType::Axis3D;

	mapKey(MoveAction, EKeys::W, false, true, EInputAxisSwizzle::YXZ);
	mapKey(MoveAction, EKeys::S, true, true, EInputAxisSwizzle::YXZ);
	mapKey(MoveAction, EKeys::A, true);
	mapKey(MoveAction, EKeys::D);
	mapKey(MoveAction, EKeys::SpaceBar, false, true, EInputAxisSwizzle::ZYX);
	mapKey(MoveAction, EKeys::LeftControl, true, true, EInputAxisSwizzle::ZYX);
	mapKey(MoveAction, EKeys::Up, false, true, EInputAxisSwizzle::YXZ);
	mapKey(MoveAction, EKeys::Down, true, true, EInputAxisSwizzle::YXZ);
	mapKey(MoveAction, EKeys::Left, true);
	mapKey(MoveAction, EKeys::Right);
	return MoveAction;
}

UInputAction* UEnhancedInputMappingContext::lookKeys(UObject* Outer)
{
	UInputAction* LookAction = NewObject<UInputAction>(Outer);
	LookAction->ValueType = EInputActionValueType::Axis2D;
	mapKey(LookAction, EKeys::Mouse2D, false, true, false);
	return LookAction;
}

UInputAction* UEnhancedInputMappingContext::mapTapKey(UObject* Outer, FKey key, float timeThreshold) {
	UInputAction* act = NewObject<UInputAction>(Outer);
	FEnhancedActionKeyMapping& mapping = MapKey(act, key);
	UInputTriggerTap* tap = NewObject<UInputTriggerTap>(Outer);
	tap->TapReleaseTimeThreshold = timeThreshold;
	mapping.Triggers.Add(tap);
	return act;
}
void UEnhancedInputMappingContext::mapKey(UInputAction* act, FKey key, bool negateX, bool negateY, bool negateZ) {
	FEnhancedActionKeyMapping& mapping = MapKey(act, key);
	
	
	UInputModifierNegate* neg = NewObject<UInputModifierNegate>(act->GetOuter());
	neg->bX = negateX;
	neg->bY = negateY;
	neg->bZ = negateZ;
	mapping.Modifiers.Add(neg);
}
void UEnhancedInputMappingContext::mapKey(UInputAction* act, FKey key, bool negate, bool swizzle, EInputAxisSwizzle order) {
	FEnhancedActionKeyMapping& mapping = MapKey(act, key);
	
	UObject * Outer = act->GetOuter();
	if (negate) {
		UInputModifierNegate* neg = NewObject<UInputModifierNegate>(Outer);
		mapping.Modifiers.Add(neg);
	}
	if (swizzle) {
		UInputModifierSwizzleAxis* sw = NewObject<UInputModifierSwizzleAxis>(Outer);
		sw->Order = order;
		mapping.Modifiers.Add(sw);
	}
}

void UEnhancedInputMappingContext::setMapping(APlayerController * c)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(c->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(this, 0);
	}
}

