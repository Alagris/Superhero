// Fill out your copyright notice in the Description page of Project Settings.


#include "CompleteInventoryMenu.h"


void UCompleteInventoryMenu::NativeConstruct()
{
    Super::NativeConstruct();
    PlayerButton->OnClicked.AddUniqueDynamic(this, &UCompleteInventoryMenu::OnPlayerSelected);
    NpcButton->OnClicked.AddUniqueDynamic(this, &UCompleteInventoryMenu::OnNpcSelected);
    CraftingButton->OnClicked.AddUniqueDynamic(this, &UCompleteInventoryMenu::OnCraftingSelected);
    ItemListView->OnItemSelectionChanged().AddUObject(this, &UCompleteInventoryMenu::OnItemSelectionChanged);

}

