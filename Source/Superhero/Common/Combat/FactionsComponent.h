// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ISpudObject.h"
#include "Factions.h"
#include "FactionsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UFactionsComponent : public UActorComponent, public ISpudObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFactionsComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFactions* Factions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	UFaction* Faction;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
