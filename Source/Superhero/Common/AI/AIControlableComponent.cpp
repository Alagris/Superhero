// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AI/AIControlableComponent.h"

// Sets default values for this component's properties
UAIControlableComponent::UAIControlableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = false;
	// ...
}


// Called when the game starts
void UAIControlableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIControlableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

