// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIController.h"
#include "BTTask_FocusOnOpponent.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UBTTask_FocusOnOpponent : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool Focus = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 Priority = EAIFocusPriority::Gameplay;
};
