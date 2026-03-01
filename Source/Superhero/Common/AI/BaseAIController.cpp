// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include <Common/Combat/FactionsComponent.h>
#include <Common/AI/AIControlableComponent.h>
#include <Common/Character/BasicAICharacter.h>


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
	if (UFactionsComponent* f = pawn->GetComponentByClass<UFactionsComponent>()) {
		Faction = f->Faction;

	}
	if (IsValid(Faction)) {
		if (ABasicAICharacter* aic = Cast<ABasicAICharacter>(pawn)) {
			aic->TeamId = Faction->TeamId;
		}
	}
}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const {
	if (IsValid(Faction)) {
		if (UFactionsComponent* f = Other.GetComponentByClass<UFactionsComponent>()) {
			return f->getAttitude(Faction);
		}
	}
	return ETeamAttitude::Neutral;
}
