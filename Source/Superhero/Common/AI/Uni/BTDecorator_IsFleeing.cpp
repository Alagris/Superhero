// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsFleeing.h"
#include "UniversalAIController.h"
bool UBTDecorator_IsFleeing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	if (AUniversalAIController * ai = Cast<AUniversalAIController>(OwnerComp.GetAIOwner())) {
		return ai->State == ai->FleeingState;
	}
	return false;
}