// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionSystem.h>
#include "BaseAIController.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	virtual void OnPossess(APawn* pawn) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFaction* Faction;


	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override {
		Super::SetGenericTeamId(NewTeamID);
		UAIPerceptionSystem::GetCurrent(GetWorld())->UpdateListener(*GetAIPerceptionComponent());
	}
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;


	
};
