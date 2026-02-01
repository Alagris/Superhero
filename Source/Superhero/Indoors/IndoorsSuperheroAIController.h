// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IndoorsSuperheroAIController.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API AIndoorsSuperheroAIController : public AAIController
{
	GENERATED_BODY()
	virtual void OnPossess(APawn* pawn) override;

	
};
