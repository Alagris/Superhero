// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInvestigating.h"
#include "UniversalAIController.h"
bool UBTDecorator_IsInvestigating::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	if (AUniversalAIController * ai = Cast<AUniversalAIController>(OwnerComp.GetAIOwner())) {
		return ai->State == ai->InvestigatingState;
	}
	return false;
}