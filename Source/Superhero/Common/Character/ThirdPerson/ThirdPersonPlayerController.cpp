// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThirdPersonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include <Common/UI/GameHUD.h>
#include "ThirdPersonCharacter.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include <EnhancedInputComponent.h>

void AThirdPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void AThirdPersonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	DefaultMappingContext = NewObject<UThirdPersonInputMappingContext>(this);
	DefaultMappingContext->setMapping(this);

	
}

void AThirdPersonPlayerController::SetPawn(APawn* pawn)
{
	Super::SetPawn(pawn);
	
	ThirdPersonCharacter = Cast<AThirdPersonCharacter>(pawn);
	if (ThirdPersonCharacter) {
		//ThirdPersonCharacter->OnPossess(this);
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {

			EnhancedInputComponent->ClearActionBindings();
			// Looking
			EnhancedInputComponent->BindAction(DefaultMappingContext->LookAction, ETriggerEvent::Triggered, this, &AThirdPersonPlayerController::Look);			
			EnhancedInputComponent->BindAction(DefaultMappingContext->OpenInvAction, ETriggerEvent::Completed, this, &AThirdPersonPlayerController::TriggerInventory);
			EnhancedInputComponent->BindAction(DefaultMappingContext->PauseGameAction, ETriggerEvent::Completed, this, &AThirdPersonPlayerController::TriggerPauseGame);
			
			DefaultMappingContext->BindToThirdPerson(EnhancedInputComponent, ThirdPersonCharacter);
		}
	}
}

void AThirdPersonPlayerController::TriggerPauseGame(const FInputActionValue& Value)
{
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		hud->TriggerPauseGame(Value);
	}
}

void AThirdPersonPlayerController::TriggerInventory(const FInputActionValue& Value)
{
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		hud->TriggerInventory(Value);
	}
}

void AThirdPersonPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddPitchInput(LookAxisVector.Y);
	}
}
