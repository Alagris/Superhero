// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Character/BasicAICharacter.h"
#include "Common/AI/BaseAIController.h"
#include "Common/Character/Movement/AdvancedMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABasicAICharacter::ABasicAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UAdvancedMovementComponent>(CharacterMovementComponentName)) 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AI = CreateDefaultSubobject<UAIControlableComponent>(TEXT("AI"));
	Health = CreateDefaultSubobject<UHealth>(TEXT("Health"));
	AIControllerClass = ABaseAIController::StaticClass();
	UAdvancedMovementComponent* a = Cast<UAdvancedMovementComponent>(GetCharacterMovement());
	a->setUseAccelerationForPathFollowing(true);


}

// Called when the game starts or when spawned
void ABasicAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

