// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandedAIController.h"
#include "CommandedCharacter.h"
#include "BehaviorTree/BehaviorTree.h"


void ACommandedAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	if (ACommandedCharacter* npc = Cast<ACommandedCharacter>(pawn)) {
		if (UBehaviorTree* bt = npc->BehaviourTree) {
			UBlackboardComponent* bbc;
			UseBlackboard(bt->BlackboardAsset, bbc);
			Blackboard = bbc;
			RunBehaviorTree(bt);
		}
	}
}
