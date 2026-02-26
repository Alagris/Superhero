// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OpenableFurnitureAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UOpenableFurnitureAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsOpen=false;
};
