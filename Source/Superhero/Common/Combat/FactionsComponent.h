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
	UFactions* Factions = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	UFaction* Faction = nullptr;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadOnly)
	class UHealth* HealthComponent=nullptr;

	UPROPERTY(BlueprintReadOnly)
	class UCombatComponent* CombatComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	class UClothingSystem* ClothingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	class UInventory* InventoryComponent = nullptr;

	UPROPERTY()
	FGenericTeamId TeamId;

	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	ETeamAttitude::Type getAttitude(UFaction* other) {
		if (IsValid(Factions)) {
			return Factions->getAttitude(Faction, other);
		}
		return ETeamAttitude::Neutral;
	}
	ETeamAttitude::Type getAttitude(UFactionsComponent* other) {
		return getAttitude(other->Faction);
	}
	inline FGenericTeamId getTeamId() const {
		return TeamId;
	}
};
