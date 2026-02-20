// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/UI/Inventory/ItemListEntry.h"
#include "Components/Border.h"
#include "BasicItemListEntry.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UBasicItemListEntry : public UItemListEntry
{
	GENERATED_BODY()

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
public:


	UPROPERTY(meta = (BindWidget))
	UBorder* RowBorder;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ValueLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageLabel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FSlateColor EquippedColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FSlateColor UnequippedColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor SelectedBorderColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor UnselectedBorderColor;
	
	virtual void RefreshItem_Implementation() override;

	
};
