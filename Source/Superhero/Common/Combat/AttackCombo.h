// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackCombo.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UAttackCombo : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* AttackAnim;

	virtual UAttackCombo* getNext(bool isPrimary, bool isHeavy) { return nullptr; }
};
