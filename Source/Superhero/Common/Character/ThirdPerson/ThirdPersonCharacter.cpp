// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Kismet/KismetSystemLibrary.h>



DEFINE_LOG_CATEGORY(LogThirdPersonCharacter);

AThirdPersonCharacter::AThirdPersonCharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	USkeletalMeshComponent* playerMesh = GetMesh();
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PhysicsHandle = CreateDefaultSubobject<UInteractPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetRelativeTransform(FTransform(FVector(0., 0., 40.)));
	FollowCamera->SetActive(false);

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(playerMesh, "head"); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FirstPersonCamera->SetRelativeTransform(FTransform(FRotator(0, 90, -90), FVector(0, 10, 0)));
	FirstPersonCamera->bUsePawnControlRotation = true; // Camera rotates relative to head
	FirstPersonCamera->SetActive(true);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}



void AThirdPersonCharacter::TriggerCameraZoomOut(const FInputActionValue& Value) {
	if (this->FirstPersonCamera->IsActive()) {
		ToggleCamera(false);
	}
	else { // in third person view
		this->GetCameraBoom()->TargetArmLength = FMath::Min(this->GetCameraBoom()->TargetArmLength + ZoomSpeed, MaxZoomOut);
	}
}
void AThirdPersonCharacter::TriggerCameraZoom(const FInputActionValue& Value) {
	float zoom = Value.Get<FInputActionValue::Axis1D>();
	if (zoom > 0)TriggerCameraZoomIn(Value);
	else TriggerCameraZoomOut(Value);
}


void AThirdPersonCharacter::getRay(double length, Ray& ray) {
	FTransform transform = GetCurrentCamera()->GetComponentTransform();
	ray.start = transform.GetLocation();
	//ray.start.Z += 20.;
	FVector forward = transform.GetRotation().GetForwardVector();
	ray.start += forward * CameraBoom->TargetArmLength;
	ray.end = ray.start + forward * length;
}


FVector AThirdPersonCharacter::getRayEnd(double length) {
	Ray ray;
	getRay(length, ray);
	return ray.end;
}

bool AThirdPersonCharacter::CastRay(FHitResult& OutHit, float distance, const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypesArray) {
	Ray ray;
	getRay(distance, ray);
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);
	return UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), ray.start, ray.end, objectTypesArray, false, actorsToIgnore, EDrawDebugTrace::None, OutHit, true);
}
void AThirdPersonCharacter::TriggerInteractStart(const FInputActionValue& Value) {
	FHitResult OutHit;
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;
	objectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));
	//objectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	objectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	if (CastRay(OutHit, InteractDistance, objectTypesArray)) {
		PhysicsHandle->InteractStart(OutHit);
	}
}

void AThirdPersonCharacter::TriggerCameraZoomIn(const FInputActionValue& Value) {

	if (this->FollowCamera->IsActive()) { // in third person view
		float arm = this->GetCameraBoom()->TargetArmLength;
		if (arm <= MinZoomOut) {
			ToggleCamera(true);
		}
		else {
			this->GetCameraBoom()->TargetArmLength = FMath::Min(arm - ZoomSpeed, MaxZoomOut);
		}
	}
}

void AThirdPersonCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

