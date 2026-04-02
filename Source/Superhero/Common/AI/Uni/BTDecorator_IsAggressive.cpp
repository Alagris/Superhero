// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsAggressive.h"
#include "UniversalAIController.h"
bool UBTDecorator_IsAggressive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	if (AUniversalAIController * ai = Cast<AUniversalAIController>(OwnerComp.GetAIOwner())) {
		return ai->State == ai->AggressiveState;
	}
	return false;
}