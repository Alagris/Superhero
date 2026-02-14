// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ISpudObject.h"
#include <EnhancedInputLibrary.h>
#include "IndoorsPawn.generated.h"

class AIndoorsPlayerController;


UCLASS()
class SUPERHERO_API AIndoorsPawn : public APawn, public ISpudObject
{
	GENERATED_BODY()

	
public:
	// Sets default values for this pawn's properties
	AIndoorsPawn(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPawnMovementComponent* GameMovement;
	AIndoorsPlayerController* IndoorsController;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void Move(const FInputActionValue& Value);


	void OnPossessed(AIndoorsPlayerController* c);

};
