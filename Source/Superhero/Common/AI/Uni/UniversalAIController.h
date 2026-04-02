// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AI/BaseAIController.h"
#include "UniversalAIController.generated.h"


USTRUCT(BlueprintType)
struct FKnownEnemy {
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	UFactionsComponent* FactionComponent;

	UPROPERTY(BlueprintReadOnly)
	FVector LastKnownLocation;
};


UCLASS()
class SUPERHERO_API AUniversalAIController : public ABaseAIController
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	int IdleState=0;

	UPROPERTY(EditDefaultsOnly)
	int FollowState=1;

	UPROPERTY(EditDefaultsOnly)
	int AggressiveState=2;

	UPROPERTY(EditDefaultsOnly)
	int FleeingState=3;

	UPROPERTY(EditDefaultsOnly)
	int InvestigatingState = 4;

	UPROPERTY(BlueprintReadOnly, SaveGame)
	int State=0;

	UPROPERTY(BlueprintReadOnly, SaveGame)
	FKnownEnemy FocusEnemy;

	void setEnemy(UFactionsComponent* factionsComponent, FAIStimulus& Stimulus) {
		FocusEnemy.FactionComponent = factionsComponent;
	}

	void OnSight(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus) override;
	void OnHearing(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus) override;
	void OnDamage(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus) override;
};
