// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicItemListEntry.h"
#include <Common/Inventory/ItemInstance.h>

void UBasicItemListEntry::RefreshItem_Implementation() {
	Super::RefreshItem_Implementation();
	if (IsValid(Item)) {
		const UItem * t = Item->ItemType;
		WeightLabel->SetText(FText::AsNumber(t->Weight));
		ValueLabel->SetText(FText::AsNumber(t->Value));
		ArmorLabel->SetText(FText::AsNumber(t->getArmor()));
		DamageLabel->SetText(FText::AsNumber(t->getDamage()));

		FSlateColor newColor = Item->isEquipped() ? EquippedColor : UnequippedColor;
		
		ItemName->SetColorAndOpacity(newColor);
		
	}
}


void UBasicItemListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	RowBorder->SetBrushColor(bIsSelected ? SelectedBorderColor : UnselectedBorderColor);
}
