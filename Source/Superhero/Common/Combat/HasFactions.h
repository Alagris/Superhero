// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FactionsComponent.h"
#include "HasFactions.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasFactions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SUPERHERO_API IHasFactions
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UFactionsComponent* getFactionsComponent() const = 0;
};
