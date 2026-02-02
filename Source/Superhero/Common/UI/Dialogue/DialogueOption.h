// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "Blueprint/IUserObjectListEntry.h"
#include "DialogueOption.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UDialogueOption : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;



	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextOption;


	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY()
	TObjectPtr<class UDialogueResponse> DialogueResponse;

	UPROPERTY()
	class UDialogueResponseListView* Parent;

	UFUNCTION()
	void OnOptionClick();

};
