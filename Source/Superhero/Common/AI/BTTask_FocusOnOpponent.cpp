// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FocusOnOpponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Common/Combat/CombatComponent.h>

EBTNodeResult::Type UBTTask_FocusOnOpponent::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
		AAIController* c = OwnerComp.GetAIOwner();
		if(Focus){
			if (UCombatComponent* combat = c->GetPawn()->GetComponentByClass<UCombatComponent>()) {
				if (IsValid(combat->AutoAimTarget)) {
					//UMovementComponent* mov = c->GetPawn()->GetMovementComponent();
					//mov->

					c->SetFocus(combat->AutoAimTarget, Priority);
				}
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		else {
			c->ClearFocus(Priority);
		}
		return EBTNodeResult::Failed;
	
}