// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsFollowing.h"
#include "UniversalAIController.h"
bool UBTDecorator_IsFollowing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	if (AUniversalAIController * ai = Cast<AUniversalAIController>(OwnerComp.GetAIOwner())) {
		return ai->State == ai->FollowState;
	}
	return false;
}