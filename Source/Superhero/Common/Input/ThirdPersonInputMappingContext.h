// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Input/EnhancedInputMappingContext.h"
#include "ThirdPersonInputMappingContext.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UThirdPersonInputMappingContext : public UEnhancedInputMappingContext
{
	GENERATED_BODY()
	
public:

	/** Pause Game Action */
	UPROPERTY()
	UInputAction* PauseGameAction;

	/** Jump Input Action */
	UPROPERTY()
	UInputAction* JumpAction;

	/** Slow walk Input Action */
	UPROPERTY()
	UInputAction* SlowWalkAction;

	/** Run Input Action */
	UPROPERTY()
	UInputAction* RunAction;

	/** Move Input Action */
	UPROPERTY()
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY()
	UInputAction* LookAction;

	/** Zoom In Input Action */
	UPROPERTY()
	UInputAction* ZoomAction;

	/** Crouch Input Action */
	UPROPERTY()
	UInputAction* CrouchAction;

	/** Attack Input Action */
	UPROPERTY()
	UInputAction* InteractAction;

	virtual void initialize(APlayerController* c) override{
		MoveAction = moveKeys(c);
		LookAction = lookKeys(c);
		SlowWalkAction = makeSlowWalkAction(c);
		RunAction = makeRunAction(c);
		JumpAction = makeJumpAction(c);
		InteractAction = makeInteractAction(c);
		ZoomAction = makeZoomAction(c);
		CrouchAction = makeCrouchAction(c);
		PauseGameAction = makePauseGameAction(c);

	}
	virtual void setMapping(APlayerController* c)override {
		if (MoveAction == nullptr) {
			initialize(c);
		}
		Super::setMapping(c);
	}
	void BindToThirdPerson(class UEnhancedInputComponent* EnhancedInputComponent, class AThirdPersonCharacter * a);
};
