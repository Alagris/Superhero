// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Common/Inventory/Inventory.h>
#include <Common/Props/Actor/ItemActor.h>
#include "ItemListView.h"
#include "InventoryPage.h"
#include "InventoryMenu.generated.h"


/**
 * 
 */
UCLASS()
class SUPERHERO_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

	


	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void BeginDestroy() override {
		Super::BeginDestroy();
		if (NpcInv != nullptr) {
			NpcInv->InventoryWidget = nullptr;
		}
		if (PlayerInv != nullptr) {
			PlayerInv->InventoryWidget = nullptr;
		}
	}
public:

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

	inline void setPage(EInventoryPage page) {
		if (Page != page) {
			setPageForce(page);
		}
	}

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UItemListView* ItemListView;


	virtual bool setup(class AGameHUD* hud, APlayerController* playerController, UInventory* player, UInventory* npc=nullptr, bool exchangeForFree = false, EInventoryPage page = EInventoryPage::PLAYER);

	virtual void onItemSelected(UItemInstance* item);

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
	void clearItems();
	void addAllItems();
	void resetItems() {
		clearItems();
		addAllItems();
	}
protected:
	virtual void setPlayerSelected(bool playerSelected);
	virtual bool openCrafting() {
		return false;
	}
private:
	
	
	inline void setPageForce(EInventoryPage page) {
		switch (page) {
		case EInventoryPage::PLAYER:
			setPlayerSelected(true);
			break;
		case EInventoryPage::NPC:
			setPlayerSelected(false);
			break;
		case EInventoryPage::CRAFTING:
			if (!openCrafting()) {
				setPlayerSelected(true);
			}
			break;
		}
	}
};
