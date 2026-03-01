// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GenericTeamAgentInterface.h"
#include "Faction.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UFaction : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGenericTeamId TeamId = FGenericTeamId::NoTeam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int FactionIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFactions * Owner;
	
};
