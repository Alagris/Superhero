// Fill out your copyright notice in the Description page of Project Settings.


#include "Indoors/IndoorsPawn.h"
#include "InputActionValue.h"
#include "GameFramework/SpectatorPawnMovement.h"
#include "Indoors/IndoorsPlayerController.h"


// Sets default values
AIndoorsPawn::AIndoorsPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameMovement = CreateDefaultSubobject<USpectatorPawnMovement>(TEXT("Movement"));
	IndoorsController = nullptr;


}

// Called when the game starts or when spawned
void AIndoorsPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndoorsPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIndoorsPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIndoorsPawn::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector MovementVector = Value.Get<FInputActionValue::Axis3D>();
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		AddMovementInput(Rotation.RotateVector(MovementVector));
	}
}

void AIndoorsPawn::LeftClick(const FInputActionValue& Value)
{
}

void AIndoorsPawn::RightClick(const FInputActionValue& Value)
{
}

void AIndoorsPawn::OnPossessed(AIndoorsPlayerController* c)
{
	this->IndoorsController = c;
	this->IndoorsController->GameCharacter = this;
}

