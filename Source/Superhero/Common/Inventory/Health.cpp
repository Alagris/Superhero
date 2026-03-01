// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Inventory/Health.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = false;
	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UHealth::InitializeComponent()
{
	Super::InitializeComponent();
}



// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (HealthBar != nullptr) {
		HealthBar->Health->SetPercent(getHealthPercent());
		if (APlayerController* c = GetWorld()->GetFirstPlayerController()) {
			FVector camPos = c->PlayerCameraManager->GetCameraLocation();
			FRotator rot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), camPos);
			HealthBarComponent->SetWorldRotation(rot);
		}
	}

}