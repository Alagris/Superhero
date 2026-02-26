// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/UI/Inventory/InventoryMenu.h"
#include "Common/UI/Inventory/ItemListView.h"
#include "Common/UI/Inventory/ItemListEntry.h"
#include "Common/UI/GameHUD.h"
#include <EnhancedInputComponent.h>

void UInventoryMenu::NativeConstruct()
{
    ItemListView->Root = this;
    
}


bool UInventoryMenu::setup(AGameHUD* hud, APlayerController* playerController, UInventory* player, UInventory* npc, bool exchangeForFree, EInventoryPage page)
{
	PlayerInv = player;
    NpcInv = npc;
    PlayerController = playerController;
    Hud = hud;
    ExchangeForFree = exchangeForFree;
    Page = page;

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(playerController->InputComponent)) {
        EnhancedInputComponent->BindAction(hud->UIInput->Interact, ETriggerEvent::Triggered, this, &UInventoryMenu::OnInteract);
        EnhancedInputComponent->BindAction(hud->UIInput->Drop, ETriggerEvent::Triggered, this, &UInventoryMenu::OnDrop);
        EnhancedInputComponent->BindAction(hud->UIInput->Up, ETriggerEvent::Triggered, this, &UInventoryMenu::OnUp);
        EnhancedInputComponent->BindAction(hud->UIInput->Down, ETriggerEvent::Triggered, this, &UInventoryMenu::OnDown);
        EnhancedInputComponent->BindAction(hud->UIInput->Exit, ETriggerEvent::Triggered, this, &UInventoryMenu::OnExit);
        EnhancedInputComponent->BindAction(hud->UIInput->Enter, ETriggerEvent::Triggered, this, &UInventoryMenu::OnEnter);
        EnhancedInputComponent->BindAction(hud->UIInput->Inventory, ETriggerEvent::Triggered, this, &UInventoryMenu::OnExit);
        EnhancedInputComponent->BindAction(hud->UIInput->Scroll, ETriggerEvent::Triggered, this, &UInventoryMenu::OnScroll);
    }
    hud->UIInput->setMapping(playerController);
    setPage(page, true);
	return true;
}


void UInventoryMenu::OnScroll(const FInputActionValue& Value)
{
    float zoom = Value.Get<FInputActionValue::Axis1D>();
    moveSelection(zoom > 0 ? 1 : -1);
}

void UInventoryMenu::exit()
{
    OnInventoryCloseSignature.Broadcast(this);
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent)) {

        EnhancedInputComponent->ClearBindingsForObject(this);
    }
    
    Hud->hideInventoryMenu();
    
}

void UInventoryMenu::updateItem(UItemInstance* item)
{
    UItemListEntry* row = ItemListView->GetEntryWidgetFromItem<UItemListEntry>(item);
    if (row) {
        check(row->Item == item);
        row->RefreshItem();
    }
}

bool UInventoryMenu::setPlayerSelected(bool playerSelected, bool forceRefresh)
{
    EInventoryPage desiredPage = playerSelected ? EInventoryPage::PLAYER : EInventoryPage::NPC;
    if (forceRefresh || Page != desiredPage) {
        if (UInventory* inv = playerSelected ? PlayerInv : NpcInv) {
            Page = desiredPage;
            PlayerInv->InventoryWidget = playerSelected ? this : nullptr;
            if (NpcInv != nullptr)NpcInv->InventoryWidget = playerSelected ? nullptr : this;
            check(inv != nullptr);
            ItemListView->Inv = inv;
            resetItems();
            return true;
        }
    }
    return false;
}
