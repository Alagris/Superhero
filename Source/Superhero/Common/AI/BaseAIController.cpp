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
	FactionComponent = pawn->GetComponentByClass<UFactionsComponent>();
}

void ABaseAIController::OnUnPossess()
{	
	FactionComponent = nullptr;
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
	if (IsValid(FactionComponent)) {
		if (const IHasFactions* hasFactions = Cast<IHasFactions>(&Other)) {
			if (UFactionsComponent* factionsComponent = hasFactions->getFactionsComponent()) {
				return factionsComponent->getAttitude(FactionComponent);
			}
		}
	}
	return ETeamAttitude::Neutral;
}

void ABaseAIController::onActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (IsValid(FactionComponent)) {
		if (IHasFactions* hasFactions = Cast<IHasFactions>(Actor)) {
			if (UFactionsComponent* factionsComponent = hasFactions->getFactionsComponent()) {
				ETeamAttitude::Type att = factionsComponent->getAttitude(FactionComponent);
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
