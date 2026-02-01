// Fill out your copyright notice in the Description page of Project Settings.


#include "Indoors/IndoorsSuperheroAIController.h"
#include "IndoorsSuperhero.h"


void AIndoorsSuperheroAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	if (AIndoorsSuperhero* npc = Cast<AIndoorsSuperhero>(pawn)) {
		if (UBehaviorTree* bt = npc->BehaviourTree) {
			UBlackboardComponent* bbc;
			UseBlackboard(bt->BlackboardAsset, bbc);
			Blackboard = bbc;
			RunBehaviorTree(bt);
		}
	}
}
