// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include <Common/Combat/FactionsComponent.h>
#include <Common/AI/AIControlableComponent.h>
#include <Common/Character/BasicAICharacter.h>
#include <Common/Combat/HasFactions.h>


void ABaseAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	if (UAIControlableComponent* ai = pawn->GetComponentByClass<UAIControlableComponent>()) {
		if (UBehaviorTree* bt = ai->BehaviourTree) {
			UBlackboardComponent* bbc;
			UseBlackboard(bt->BlackboardAsset, bbc);
			Blackboard = bbc;
			RunBehaviorTree(bt);
		}
	}
	Faction = nullptr;
	FactionComponent = pawn->GetComponentByClass<UFactionsComponent>();
	if (FactionComponent) {
		Faction = FactionComponent->Faction;
		CombatComponent = Cast<UCombatComponent>(FactionComponent);
		if (CombatComponent) {
			ClothingComponent = CombatComponent->Clothing;
		}
	}
	else {
		CombatComponent = nullptr;
	}
	if(CombatComponent==nullptr){
		ClothingComponent = pawn->GetComponentByClass<UClothingSystem>();
	}
	HealthComponent = pawn->GetComponentByClass<UHealth>();

	if (IsValid(Faction)) {
		if (ABasicAICharacter* aic = Cast<ABasicAICharacter>(pawn)) {
			aic->TeamId = Faction->TeamId;
		}
	}
}

void ABaseAIController::OnUnPossess()
{	
	Faction = nullptr;
	FactionComponent = nullptr;
	HealthComponent = nullptr;
	CombatComponent = nullptr;
	ClothingComponent = nullptr;
}

ABaseAIController::ABaseAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->SightRadius = 60;
	SightConfig->SightRadius = 500;
	Perception->ConfigureSense(*SightConfig);

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->HearingRange = 500;
	Perception->ConfigureSense(*HearingConfig);

	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	//DamageConfig->DetectionByAffiliation.bDetectEnemies = true;
	//DamageConfig->DetectionByAffiliation.bDetectNeutrals = true;
	//DamageConfig->DetectionByAffiliation.bDetectFriendlies = true;
	Perception->ConfigureSense(*DamageConfig);


	Perception->SetDominantSense(SightConfig->GetSenseImplementation());
	Perception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::onActorPerceptionUpdated);
	Perception->OnTargetPerceptionForgotten.AddUniqueDynamic(this, &ABaseAIController::onActorPerceptionForgetUpdated);

}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const {
	if (IsValid(Faction)) {
		if (const IHasFactions* hasFactions = Cast<IHasFactions>(&Other)) {
			if (UFactionsComponent* factionsComponent = hasFactions->getFactionsComponent()) {
				return factionsComponent->getAttitude(Faction);
			}
		}
	}
	return ETeamAttitude::Neutral;
}

void ABaseAIController::onActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (IsValid(Faction)) {
		if (IHasFactions* hasFactions = Cast<IHasFactions>(Actor)) {
			if (UFactionsComponent* factionsComponent = hasFactions->getFactionsComponent()) {
				ETeamAttitude::Type att = factionsComponent->getAttitude(Faction);
				if (Stimulus.Type==SightConfig->GetSenseID()) {
					OnSight(att, factionsComponent, Stimulus);
				}else if (Stimulus.Type == HearingConfig->GetSenseID()) {
					OnHearing(att, factionsComponent, Stimulus);
				}else if (Stimulus.Type == DamageConfig->GetSenseID()) {
					OnDamage(att, factionsComponent, Stimulus);
				}
			}
		}
	}
}
