// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsIdle.h"
#include "UniversalAIController.h"
bool UBTDecorator_IsIdle::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	if (AUniversalAIController * ai = Cast<AUniversalAIController>(OwnerComp.GetAIOwner())) {
		return ai->State == ai->IdleState;
	}
	return false;
}