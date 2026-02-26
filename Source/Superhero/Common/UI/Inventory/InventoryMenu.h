// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Common/Inventory/Inventory.h>
#include <Common/Props/Actor/ItemActor.h>
#include "ItemListView.h"
#include "InventoryPage.h"
#include <Common/Props/Crafting/Recipes.h>
#include "InventoryMenu.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryCloseSignature, class UInventoryMenu* /* inventory */);
/**
 * 
 */
UCLASS()
class SUPERHERO_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

	
protected:

	virtual void NativeConstruct() override;

	virtual void BeginDestroy() override {
		Super::BeginDestroy();
		unbindInventories();
	}
public:

	void unbindInventories() {
		if (NpcInv != nullptr) {
			NpcInv->InventoryWidget = nullptr;
		}
		if (PlayerInv != nullptr) {
			PlayerInv->InventoryWidget = nullptr;
		}
	}

	FOnInventoryCloseSignature OnInventoryCloseSignature;

	UPROPERTY()
	URecipes* Recipes;

	UPROPERTY()
	UInventory* PlayerInv;

	UPROPERTY()
	UInventory* NpcInv;

	UPROPERTY()
	class AGameHUD* Hud;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	EInventoryPage Page = EInventoryPage::PLAYER;

	UPROPERTY()
	bool ExchangeForFree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* TradingSound;

	inline bool isExchanging() const {
		return IsValid(NpcInv);
	}
	inline bool isTrading() const {
		return isExchanging() && !ExchangeForFree;
	}
	inline bool isBuying() const {
		return isTrading() && Page == EInventoryPage::NPC;
	}

	

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UItemListView* ItemListView;


	virtual bool setup(class AGameHUD* hud, APlayerController* playerController, UInventory* player, UInventory* npc=nullptr, bool exchangeForFree = false, EInventoryPage page = EInventoryPage::PLAYER);


	void OnUp(const struct FInputActionValue& Value) {
		moveSelection(-1);
	}

	void OnDown(const struct FInputActionValue& Value) {
		moveSelection(1);
	}

	void moveSelection(int offset) {
		int n = ItemListView->GetNumItems();
		if (n > 0) {
			UObject* o = ItemListView->GetSelectedItem();
			int i = o == nullptr ? 0 : ItemListView->GetIndexForItem(o);
			ItemListView->SetSelectedIndex((i + offset) % n);
		}
	}

	void OnExit(const struct FInputActionValue& Value) {
		exit();
	}

	void OnEnter(const struct FInputActionValue& Value) {

	}

	void OnInteract(const struct FInputActionValue& Value) {
		useSelected();
	}

	void OnDrop(const struct FInputActionValue& Value) {
		dropSelected();
	}

	void OnScroll(const FInputActionValue& Value);
	void useSelected() {
		if (UItemInstance* item = getSelected()) {
			item->use(PlayerInv->GetOwner());
		}
	}
	void exit();
	void dropSelected() {
		if (UItemInstance* item = getSelected()) {
			dropItem(item);
		}
	}
	UItemInstance* getSelected() const {
		return ItemListView->GetSelectedItem<UItemInstance>();
	}
	void removeItem(UItemInstance* item) {
		ItemListView->RemoveItem(item);
	}
	void addItem(UItemInstance* item) {
		ItemListView->AddItem(item);
	}
	void dropItem(UItemInstance* item, int count = 1) {
		AItemActor* dropped = item->drop(count, PlayerInv->GetOwner());
		if (dropped->Item==item) {
			removeItem(item);
		}
		else {
			updateItem(item);
		}
	}
	void updateItem(UItemInstance* item);
	void clearItems() {
		ItemListView->ClearListItems();
	}
	void addAllItems() {
		for (auto& entry : ItemListView->Inv->Items) {
			ItemListView->AddItem(entry.Value);
		}
		if (ItemListView->GetNumItems() > 0) {
			ItemListView->SetSelectedIndex(0);
		}
	}
	void resetItems() {
		clearItems();
		addAllItems();
	}

	virtual bool setPlayerSelected(bool playerSelected, bool forceRefresh=false);
	virtual bool openCrafting(bool forceRefresh=false) {
		return false;
	}
	
	
	inline void setPage(EInventoryPage page, bool forceRefresh=false) {
		if (forceRefresh || Page != page) {
			switch (page) {
			case EInventoryPage::PLAYER:
				setPlayerSelected(true, forceRefresh);
				break;
			case EInventoryPage::NPC:
				setPlayerSelected(false, forceRefresh);
				break;
			case EInventoryPage::CRAFTING:
				if (!openCrafting(forceRefresh)) {
					setPlayerSelected(true, forceRefresh);
				}
				break;
			}
		}
	}
};
