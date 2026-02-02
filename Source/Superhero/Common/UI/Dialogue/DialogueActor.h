// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueActor.generated.h"

UINTERFACE(MinimalAPI)
class UDialogueActor : public UInterface
{
	GENERATED_BODY()

};


class SUPERHERO_API IDialogueActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
	void OnDialogueEntered(class APlayerController * Player);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
	void OnDialogueExited(class APlayerController* Player);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
	FText GetCharacterName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
	void OnPlayDialogueAnim(UAnimMontage* Anim);
};
