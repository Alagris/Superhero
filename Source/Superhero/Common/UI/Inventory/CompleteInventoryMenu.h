// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Common/Inventory/Health.h"
#include "Common/Inventory/NameComponent.h"
#include "Common/UI/Inventory/InventoryMenu.h"
#include "CompleteInventoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UCompleteInventoryMenu : public UInventoryMenu
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor PressedButtonColor = FLinearColor(1, 1, 1, 0.3f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor NotPressedButtonColor = FLinearColor(0, 0, 0, 0);


	void resetButtonColors() {
		FButtonStyle pressedStyle = PlayerButton->GetStyle();
		FButtonStyle notPressedStyle = pressedStyle;
		pressedStyle.Normal.TintColor = FSlateColor(PressedButtonColor);
		notPressedStyle.Normal.TintColor = FSlateColor(NotPressedButtonColor);

		NpcButton->SetStyle(Page == EInventoryPage::NPC ? pressedStyle : notPressedStyle);
		PlayerButton->SetStyle(Page == EInventoryPage::PLAYER ? pressedStyle : notPressedStyle);
		CraftingButton->SetStyle(Page == EInventoryPage::CRAFTING ? pressedStyle : notPressedStyle);


	}

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//UListView* IngredientListView;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	FText DefaultPlayerName = FText::FromString("Player");


	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	FText DefaultNpcName = FText::FromString("Other");

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* Header;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* CraftingButton;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* NpcButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* PlayerButton;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* NpcName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* PlayerName;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UWidget* StatusContainer;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* Health;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* Stamina;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* Money;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* NpcMoney;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	UWidget* NpcMoneyContianer;

	UWidget* getNpcMoneyContainer() {
		return IsValid(NpcMoneyContianer) ? NpcMoneyContianer : NpcMoney;
	}

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UWidget* DetailsPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* DetailsItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailsWeightVal;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailsValueVal;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailsArmorVal;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailsDamageVal;


	UFUNCTION()
	void OnPlayerSelected() {
		setPlayerSelected(true);
	}
	UFUNCTION()
	void OnNpcSelected() {
		setPlayerSelected(false);
	}
	UFUNCTION()
	void OnCraftingSelected() {
		openCrafting();
	}
	UFUNCTION()
	void OnItemSelectionChanged(UObject* obj) {
		if (UItemInstance* i = Cast<UItemInstance>(obj)) {
			const UItem* item = i->ItemType;
			setDetails(item);
		}
		else if (URecipe* r = Cast<URecipe>(obj)) {
			/*
			setDetails(recipe->OutputItem);
			const TArray<FIngredient>& in = recipe->Ingredients;
			IngredientObjCache.SetNum(in.Num(), EAllowShrinking::No);
			IngredientListView->ClearListItems();
			for (int i = 0; i < in.Num(); i++) {
				if (IngredientObjCache[i] == nullptr) {
					IngredientObjCache[i] = NewObject<UIngredientEntryObject>();
					IngredientObjCache[i]->IngredientIndex = i;
					IngredientObjCache[i]->PlayerInv = PlayerInventory;
				}
				IngredientObjCache[i]->Recipe = recipe;
				IngredientListView->AddItem(IngredientObjCache[i]);
			}
			IngredientListView->RegenerateAllEntries();
			*/
		}
	}

	virtual bool openCrafting(bool forceRefresh=false) override {
		if (forceRefresh || Page != EInventoryPage::CRAFTING) {
			if (IsValid(Recipes)) {
				//IngredientListView->SetVisibility(ESlateVisibility::Visible);
				ItemListView->Inv = PlayerInv;
				ItemListView->SetListItems(Recipes->Recipes);
				Page = EInventoryPage::CRAFTING;
				resetButtonColors();
				return true;
			}
		}
		return false;
	}

	void setDetails(const UItem* i) {
		DetailsItemName->SetText(i->Name);
		DetailsWeightVal->SetText(FText::FromString(FString::FromInt(i->Weight)));
		DetailsValueVal->SetText(FText::FromString(FString::FromInt(i->Value)));
		DetailsArmorVal->SetText(FText::FromString(FString::FromInt(i->getArmor())));
		DetailsDamageVal->SetText(FText::FromString(FString::FromInt(i->getDamage())));
	}


	void updateMoney()
	{
		Money->SetText(FText::FromString(FString::FromInt(PlayerInv->Money)));
		if (IsValid(NpcInv)) {
			NpcMoney->SetText(FText::FromString(FString::FromInt(NpcInv->Money)));
		}
	}
	virtual UHealth* updateStatus() {
		if (UHealth* h = PlayerInv->GetOwner()->GetComponentByClass<UHealth>()) {
			StatusContainer->SetVisibility(ESlateVisibility::Visible);
			Health->SetText(FText::FromString(FString::FromInt(h->Health) + "/" + FString::FromInt(h->MaxHealth)));
			Stamina->SetText(FText::FromString(FString::FromInt(h->Stamina) + "/" + FString::FromInt(h->MaxStamina)));
			return h;
		}
		else {
			StatusContainer->SetVisibility(ESlateVisibility::Collapsed);
			return nullptr;
		}
	}

	virtual bool setPlayerSelected(bool playerSelected, bool forceRefresh = false) override {
		if (Super::setPlayerSelected(playerSelected, forceRefresh)) {
			//IngredientListView->SetVisibility(ESlateVisibility::Collapsed);

			getNpcMoneyContainer()->SetVisibility(isBuying() ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
			updateMoney();
			resetButtonColors();
			return true;
		}
		return false;
	}

	virtual bool setup(class AGameHUD* hud, APlayerController* playerController, UInventory* player, UInventory* npc = nullptr, bool exchangeForFree = false, EInventoryPage page = EInventoryPage::PLAYER) override {
		Super::setup(hud, playerController, player, npc, exchangeForFree, page);
		CraftingButton->SetVisibility(IsValid(Recipes) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		if (UNameComponent* palyerName = player->GetOwner()->GetComponentByClass<UNameComponent>()) {
			PlayerName->SetText(palyerName->CharacterName);
		}
		else {
			PlayerName->SetText(DefaultPlayerName);
		}
		
		if (IsValid(NpcInv)) {
			NpcButton->SetVisibility(ESlateVisibility::Visible);
			if (UNameComponent* name = NpcInv->GetOwner()->GetComponentByClass<UNameComponent>()) {
				NpcName->SetText(name->CharacterName);
			}
			else {
				NpcName->SetText(DefaultNpcName);
			}
		}
		else {
			NpcButton->SetVisibility(ESlateVisibility::Collapsed);
		}
		updateStatus();
		return true;
	}
	
};

