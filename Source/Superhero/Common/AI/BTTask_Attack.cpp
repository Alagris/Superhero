// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Common/Combat/CombatComponent.h>

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerBT == nullptr) {
		AAIController* c = OwnerComp.GetAIOwner();
		if (APawn* p = c->GetPawn()) {
			if (UCombatComponent* combat = p->GetComponentByClass<UCombatComponent>()) {
				if (AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()))) {
					OwnerBT = &OwnerComp;
					combat->OnAttackEnd.BindUObject(this, &UBTTask_Attack::OnAttackEnd);
					combat->SetAutoAimTarget(target);
					combat->performAttack(IsPrimary, IsHeavy);
					return EBTNodeResult::InProgress;
				}
			}

		}
		return EBTNodeResult::Failed;
	}
	else {
		return EBTNodeResult::InProgress;
	}
}

void UBTTask_Attack::OnAttackEnd(UCombatComponent* combat)
{
	if (IsValid(OwnerBT)) {
		FinishLatentTask(*OwnerBT, EBTNodeResult::Succeeded);
		OwnerBT = nullptr;
	}
}
