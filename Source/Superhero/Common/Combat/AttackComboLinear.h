// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Combat/AttackCombo.h"
#include "AttackComboLinear.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UAttackComboLinear : public UAttackCombo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAttackCombo* Next;

	virtual UAttackCombo* getNext(bool isPrimary, bool isHeavy) { return Next; }
};
