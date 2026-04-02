// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionSystem.h>
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include <Common/Combat/CombatComponent.h>
#include "Perception/AIPerceptionTypes.h"
#include "ISpudObject.h"
#include <Common/Inventory/Health.h>
#include "BaseAIController.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API ABaseAIController : public AAIController, public ISpudObject
{
	GENERATED_BODY()
	virtual void OnPossess(APawn* pawn) override;

	virtual void OnUnPossess() override;
public:
	ABaseAIController();

	

	UPROPERTY(BlueprintReadOnly)
	UFactionsComponent* FactionComponent;

	
	inline class UHealth* getHealthComponent() const{
		return FactionComponent->HealthComponent;
	}
	
	inline class UCombatComponent* getCombatComponent() const {
		return FactionComponent->CombatComponent;
	}

	inline class UClothingSystem* getClothingComponent() const {
		return FactionComponent->ClothingComponent;
	}

	inline class UFaction* getFaction() const {
		return FactionComponent->Faction;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	class UAIPerceptionComponent* Perception;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;
	UPROPERTY()
	UAISenseConfig_Damage* DamageConfig;
	UPROPERTY()
	UAISenseConfig_Hearing* HearingConfig;

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override {
		Super::SetGenericTeamId(NewTeamID);
		UAIPerceptionSystem::GetCurrent(GetWorld())->UpdateListener(*GetAIPerceptionComponent());
	}
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;


	UFUNCTION()
	void onActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	virtual void onActorPerceptionForgetUpdated(AActor* Actor) {}
	
	virtual void OnSight(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus) {}
	virtual void OnHearing(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus) {}
	virtual void OnDamage(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus) {}
};
