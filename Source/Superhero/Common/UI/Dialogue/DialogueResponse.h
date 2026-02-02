// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueResponse.generated.h"

class UDialogueStage;
/**
 * 
 */
UCLASS()
class SUPERHERO_API UDialogueResponse : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerText;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDialogueStage> Next;

	UFUNCTION(BlueprintNativeEvent, Category = "Dialogue")
	void OnChosen();

	void OnChosen_Implementation() {}

	UFUNCTION(BlueprintNativeEvent, Category = "Dialogue")
	bool CheckCondition();

	bool CheckCondition_Implementation() { return true; }
	
};
