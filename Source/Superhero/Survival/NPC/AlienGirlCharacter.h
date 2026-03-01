// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Character/EnemyAICharacter.h"
#include "AlienGirlCharacter.generated.h"



USTRUCT(BlueprintType)
struct FBodyColor {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor BodyColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MaterialColorParam;

};

UCLASS()
class SUPERHERO_API AAlienGirlCharacter : public AEnemyAICharacter
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBodyColor> BodyColors;

	
};
