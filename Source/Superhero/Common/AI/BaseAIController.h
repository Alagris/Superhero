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
#include <Common/Inventory/Health.h>
#include "BaseAIController.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	virtual void OnPossess(APawn* pawn) override;

	virtual void OnUnPossess() override;

	ABaseAIController();
public:
	UPROPERTY(BlueprintReadOnly)
	class UFaction* Faction;

	UPROPERTY(BlueprintReadOnly)
	UFactionsComponent* FactionComponent;

	UPROPERTY(BlueprintReadOnly)
	UHealth* HealthComponent;

	UPROPERTY(BlueprintReadOnly)
	UCombatComponent* CombatComponent;

	UPROPERTY(BlueprintReadOnly)
	UClothingSystem* ClothingComponent;

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
