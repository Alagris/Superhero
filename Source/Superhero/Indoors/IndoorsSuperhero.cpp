// Fill out your copyright notice in the Description page of Project Settings.


#include "Indoors/IndoorsSuperhero.h"

// Sets default values
AIndoorsSuperhero::AIndoorsSuperhero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIndoorsSuperhero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndoorsSuperhero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIndoorsSuperhero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

