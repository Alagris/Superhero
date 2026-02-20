// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Common/Interact/InteractPhysicsHandleComponent.h"
#include <Camera/CameraComponent.h>
#include "ThirdPersonCharacter.generated.h"



struct Ray {
	FVector start, end;
};


DECLARE_LOG_CATEGORY_EXTERN(LogThirdPersonCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */

UCLASS(config = Superhero)
class AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** First Person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent * FirstPersonCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	UInteractPhysicsHandleComponent * PhysicsHandle;
	
	

public:

	/** Constructor */
	AThirdPersonCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SetCameraDistance(float distance) {
		if (distance < MinZoomOut) {
			ToggleCamera(true);
		}
		else {
			ToggleCamera(false);
			this->GetCameraBoom()->TargetArmLength = FMath::Min(MaxZoomOut, distance);
		}
	}
	UCameraComponent* GetCurrentCamera() {
		return FollowCamera->IsActive() ? FollowCamera : FirstPersonCamera;
	}
	inline bool IsDirectionalMovement() {
		UCharacterMovementComponent* c = GetCharacterMovement();
		return c->bOrientRotationToMovement;
	}
	/**Sets whether user can move in any direction. If false, user will move in camera direction. If true, movement will be independent from camera direction*/
	void ToggleDirectionalMovement(bool trueDirectionalMovement) {
		UCharacterMovementComponent* c = GetCharacterMovement();
		c->bOrientRotationToMovement = trueDirectionalMovement;
		c->bUseControllerDesiredRotation = !trueDirectionalMovement;
	}
	/**Toggle between first person camera and third person camera.*/
	void ToggleCamera(bool firstPersonView) {
		FollowCamera->SetActive(!firstPersonView);
		FirstPersonCamera->SetActive(firstPersonView);
		ToggleDirectionalMovement(!firstPersonView);
	}
	void getRay(double length, Ray& ray);
	FVector getRayEnd(double length);

	bool CastRay(FHitResult& OutHit, float distance, const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypesArray);



	void ToggleCrouch(const FInputActionValue& Value) {
		if (this->bIsCrouched) {
			this->TriggerUncrouch(Value);
		}
		else {
			this->TriggerCrouch(Value);
		}
	}
	void TriggerUncrouch(const FInputActionValue& Value)
	{
		this->UnCrouch();
	}
	void TriggerCrouch(const FInputActionValue& Value)
	{
		this->Crouch();
	}
	/** Called for interaction input */
	void TriggerInteractStart(const FInputActionValue& Value);
	/** Called for interaction input */
	void TriggerInteractEnd(const FInputActionValue& Value) {
		PhysicsHandle->InteractEnd();
	}
	void TriggerInteract(const FInputActionValue& Value) {
		PhysicsHandle->InteractTriggered();
	}
	/** Called for camera zoom input */
	void TriggerCameraZoomIn(const FInputActionValue& Value);
	void TriggerCameraZoomOut(const FInputActionValue& Value);
	void TriggerCameraZoom(const FInputActionValue& Value);

	
	/** Called for movement input */
	void TriggerMove(const FInputActionValue& Value)
	{
		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();

		// route the input
		DoMove(MovementVector.X, MovementVector.Y);
	}
	void TriggerJumpStart(const FInputActionValue& Value)
	{
		Jump();
	}

	void TriggerJumpEnd(const FInputActionValue& Value)
	{
		StopJumping();
	}


	/** Initialize input action bindings */
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Max interaction distance */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float InteractDistance = 300;
	/** How quickly camera zooms in/out when user scrolls*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float ZoomSpeed = 20.0;
	/** Max camera zooms in out*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float MaxZoomOut = 400.;
	/** Min camera zooms out*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float MinZoomOut = 80.0;

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);




};

