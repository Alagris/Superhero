// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Common/Input/ThirdPersonInputMappingContext.h"
#include "ThirdPersonPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class AThirdPersonCharacter;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AThirdPersonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY()
	UThirdPersonInputMappingContext* DefaultMappingContext;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	virtual void SetPawn(APawn* pawn) override;

	void TriggerPauseGame(const struct FInputActionValue& Value);

	void TriggerInventory(const struct FInputActionValue& Value);

	AThirdPersonCharacter* ThirdPersonCharacter;

	void Look(const FInputActionValue& Value);
};
