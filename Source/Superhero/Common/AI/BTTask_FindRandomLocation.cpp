// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AI/BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"



EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* c = OwnerComp.GetAIOwner();
	if (APawn* p = c->GetPawn()) {
		const FVector origin = p->GetActorLocation();
		if (UNavigationSystemV1* const nav = UNavigationSystemV1::GetCurrent(GetWorld())) {
			FNavLocation loc;
			if (nav->GetRandomPointInNavigableRadius(origin, SearchRadius, loc)) {
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
				/*
				FAIMoveRequest movReq;
				movReq.SetGoalLocation(loc);
				FPathFollowingRequestResult movResult = c->MoveTo(movReq);
				if (movResult.Code != EPathFollowingRequestResult::Failed) {
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
				*/
			}
		}
	}
	return EBTNodeResult::Failed;
}

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(const FObjectInitializer& objInit)
{

}

