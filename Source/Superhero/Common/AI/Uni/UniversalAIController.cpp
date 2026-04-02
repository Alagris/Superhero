// Fill out your copyright notice in the Description page of Project Settings.


#include "UniversalAIController.h"

void AUniversalAIController::OnSight(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus)
{
	if (attitude == ETeamAttitude::Hostile) {
		if(State==IdleState) {

		}
	}
}

void AUniversalAIController::OnHearing(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus)
{
	if (attitude == ETeamAttitude::Hostile) {

	}
}

void AUniversalAIController::OnDamage(ETeamAttitude::Type attitude, UFactionsComponent* factionsComponent, FAIStimulus& Stimulus)
{
	if (attitude == ETeamAttitude::Hostile) {

	}
}
