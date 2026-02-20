// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/Inventory/InventoryMenu.h"
#include "Common/UI/Inventory/ItemListView.h"
#include "Common/UI/Inventory/ItemListEntry.h"
#include "Common/UI/GameHUD.h"

void UInventoryMenu::NativeConstruct()
{
    ItemListView->Root = this;
}

FReply UInventoryMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    const FKey key = InKeyEvent.GetKey();
    if (key == EKeys::C || key == EKeys::Escape) {
        Hud->hideInventoryMenu();
        return FReply::Handled();
    }
    else if (key == EKeys::R) {
        UItemInstance* item = Cast<UItemInstance>(ItemListView->GetSelectedItem());
        if (item) {
            item->drop();
            
            return FReply::Handled();
        }
    }
    else if (key == EKeys::E) {
        UItemInstance* item = Cast<UItemInstance>(ItemListView->GetSelectedItem());
        if (item) {
            item->use(PlayerInv->GetOwner());
            return FReply::Handled();
        }
    }
    return FReply::Unhandled();
}

bool UInventoryMenu::setup(AGameHUD* hud, APlayerController* playerController, UInventory* player, UInventory* npc, bool exchangeForFree, EInventoryPage page)
{
	PlayerInv = player;
    NpcInv = npc;
    PlayerController = playerController;
    Hud = hud;
    ExchangeForFree = exchangeForFree;
    Page = page;
    setPageForce(page);
	return false;
}

void UInventoryMenu::onItemSelected(UItemInstance* item)
{
}

void UInventoryMenu::updateItem(UItemInstance* item)
{
    UItemListEntry* row = ItemListView->GetEntryWidgetFromItem<UItemListEntry>(item);
    if (row) {
        check(row->Item == item);
        row->RefreshItem();
    }
}

void UInventoryMenu::clearItems()
{
    ItemListView->ClearListItems();
}

void UInventoryMenu::addAllItems()
{
    for (auto& entry : ItemListView->Inv->Items) {
        ItemListView->AddItem(entry.Value);
    }

}

void UInventoryMenu::setPlayerSelected(bool playerSelected)
{
    check(playerSelected || NpcInv != nullptr);
    Page = playerSelected ? EInventoryPage::PLAYER : EInventoryPage::NPC;
    UInventory* inv = playerSelected ? PlayerInv :  NpcInv;
    PlayerInv->InventoryWidget = playerSelected ? this : nullptr;
    if (NpcInv != nullptr)NpcInv->InventoryWidget = playerSelected ? nullptr : this;
    check(inv != nullptr);
    ItemListView->Inv = inv;
    resetItems();
   
}
