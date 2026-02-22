// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Props/GunItem.h"
#include "NiagaraSystem.h"
#include "NiagaraGunItem.generated.h"

USTRUCT(BlueprintType)
struct SUPERHERO_API FUserParam
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector Value;
};
/**
 * 
 */
UCLASS()
class SUPERHERO_API UNiagaraGunItem : public UGunItem
{
	GENERATED_BODY()
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BarrelTipSocket="Tip";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* Niagara;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FUserParam> UserParams;

	virtual void attackTrigger(class UItemInstance* instance, bool isHeavy) const override;
};
