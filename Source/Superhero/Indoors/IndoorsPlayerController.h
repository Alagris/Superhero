// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <EnhancedInputSubsystemInterface.h>
#include <InputMappingContext.h>
#include "ISpudObject.h"
#include "IndoorsPlayerController.generated.h"

class UDialogueStage;
class AIndoorsSuperhero;
/**
 * 
 */
UCLASS()
class SUPERHERO_API AIndoorsPlayerController : public APlayerController, public ISpudObject
{
	GENERATED_BODY()

	/** Constructor */
	AIndoorsPlayerController();

	UInputAction* MapKey(UInputMappingContext* ctx, FKey key, EInputActionValueType type = EInputActionValueType::Boolean, bool triggerWhenPaused = false);
	UInputAction* MapTapKey(UInputMappingContext* ctx, FKey key, float timeThreshold);
//	UInputAction* MapTapOrHoldKey(UInputMappingContext* ctx, FKey key, float timeThreshold);
//	UInputAction* MapHoldThenOngoingKey(UInputMappingContext* ctx, FKey key, float timeThreshold);
//	UInputAction* MapHoldKey(UInputMappingContext* ctx, FKey key, float timeThreshold);

	void MapKey(UInputMappingContext* ctx, UInputAction* act, FKey key, bool negateX, bool negateY, bool negateZ);
	void MapKey(UInputMappingContext* ctx, UInputAction* act, FKey key, bool negate = false, bool swizzle = false, EInputAxisSwizzle order = EInputAxisSwizzle::YXZ);

	UInputAction* MapPressedKey(UInputMappingContext* ctx, FKey key);

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;

	/** Pawn initialization */
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetPawn(APawn* InPawn) override;

	void SetMapping(UInputMappingContext* ctx);
	FVector2D CumulativeLookAxisVector;
	void Look(const FInputActionValue& Value);

	void OnLeftClick(const FInputActionValue& Value);
	void StartRightClick(const FInputActionValue& Value) {
		isHoldingRMB = true;
		CumulativeLookAxisVector = FVector2D(0,0);
		
	}
	void EndRightClick(const FInputActionValue& Value);
	
	bool isHoldingRMB=false;
	/** MappingContext */
	UPROPERTY()
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY()
	UInputAction* MoveAction;

	UPROPERTY()
	UInputAction* LookAction;

	UPROPERTY()
	UInputAction* RightClick;

	UPROPERTY()
	UInputAction* LeftClick;

	UPROPERTY()
	UInputAction* PauseGameAction;


	void OnTriggerPauseGame(const FInputActionValue& Value) {
		TriggerPauseGame();
	}

	
public:
	AIndoorsSuperhero* SelectedHero;
	class AIndoorsPawn* GameCharacter;


	void TriggerPauseGame();
	bool PauseGame();
	bool UnpauseGame();
	bool CloseDialogue();
	bool OpenDialogue(APlayerController* PlayerController, class UDialogueComponent* Npc, TSoftObjectPtr<UDialogueStage> Stage);
	void OnSuperHeroSelected(class AIndoorsSuperhero* hero);
	
	
};
