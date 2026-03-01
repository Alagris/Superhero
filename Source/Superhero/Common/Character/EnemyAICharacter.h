// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Character/BasicAICharacter.h"
#include "EnemyAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API AEnemyAICharacter : public ABasicAICharacter
{
	GENERATED_BODY()
public:
	AEnemyAICharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	UCombatComponent* Combat;


	
};
