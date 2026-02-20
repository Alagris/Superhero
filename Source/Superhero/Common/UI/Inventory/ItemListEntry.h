// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "Blueprint/IUserObjectListEntry.h"
#include "ItemListEntry.generated.h"

class UInventory;

UCLASS()
class SUPERHERO_API UItemListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;


	//virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	//virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(BlueprintReadOnly)
	class UItemListView* Parent;

	UPROPERTY(BlueprintReadOnly)
	class UItemInstance* Item;

	UFUNCTION(BlueprintNativeEvent)
	void RefreshItem();

	
	virtual void UseItem();


	virtual bool canAfford() {
		return true;
	}

	UInventory* getInv()const;

	UInventory* getPlayerInv()const;

	UInventory* getNpcInv()const;

	
	class AGameHUD* getHud()const;

	APlayerController* getPlayerController()const;
};
