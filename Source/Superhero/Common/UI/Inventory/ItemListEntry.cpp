// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/Inventory/ItemListEntry.h"
#include "Common/UI/Inventory/ItemListView.h"
#include "Common/UI/Inventory/InventoryMenu.h"
#include <Common/Inventory/ItemInstance.h>
#include <Kismet/GameplayStatics.h>

void UItemListEntry::NativeConstruct()
{
	Super::NativeConstruct();
	UListViewBase* owner = GetOwningListView();
	Parent = Cast<UItemListView>(owner);
	check(IsValid(Parent));
}

void UItemListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (IsValid(Item = Cast<UItemInstance>(ListItemObject))) {
		RefreshItem();
	}
}

/*
void UItemListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	RowBorder->SetBrushColor(FLinearColor(1, 1, 1, bIsSelected ? 0.4 : 0));
}
*/

FReply UItemListEntry::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
		UseItem();
		return FReply::Handled();
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)) {
		UseItem();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UItemListEntry::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IsValid(Item)) {
		Parent->SetSelectedItem(Item);
	}
}

void UItemListEntry::RefreshItem_Implementation()
{
	if (IsValid(Item)) {
		ItemName->SetText(Item->getName());
	}
}

void UItemListEntry::UseItem()
{
	if (IsValid(Parent)) {
		UInventoryMenu* inv = Parent->Root;
		if (inv->isExchanging()) {
			if (canAfford()) {
				if (inv->Page == EInventoryPage::NPC) {
					if (inv->ExchangeForFree) {
						inv->NpcInv->transferInstance(inv->PlayerInv, Item, 1);
					}
				}
				else {
					if (inv->ExchangeForFree) {
						inv->PlayerInv->transferInstance(inv->NpcInv, Item, 1);
					}
				}
				if (!inv->ExchangeForFree) {
					if (IsValid(Parent->Root->TradingSound)) {
						UGameplayStatics::PlaySound2D(inv->PlayerInv, Parent->Root->TradingSound);
					}
					//Parent->Root->updateMoney();
					Parent->RegenerateAllEntries(); // affordibility of all items needs to be updated
					Parent->SetSelectedItem(Item);
				}

			}
		}
		else {
			Item->use(getInv()->GetOwner());
			
		}
	}
}

UInventory* UItemListEntry::getInv() const
{
	return Parent->Inv;
}

UInventory* UItemListEntry::getPlayerInv() const
{
	return Parent->Root->PlayerInv;
}

UInventory* UItemListEntry::getNpcInv() const
{
	return Parent->Root->NpcInv;
}

AGameHUD* UItemListEntry::getHud() const
{
	return Parent->Root->Hud;
}

APlayerController* UItemListEntry::getPlayerController() const
{
	return Parent->Root->PlayerController;
}
