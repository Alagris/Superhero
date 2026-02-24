// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include <Common/AI/AIControlableComponent.h>


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
}
