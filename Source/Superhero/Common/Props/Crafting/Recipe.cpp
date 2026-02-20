// Fill out your copyright notice in the Description page of Project Settings.


#include "Recipe.h"
#include "Common/Inventory/Inventory.h"

void URecipe::make(UInventory* inv) const
{
	check(canMake(inv));
	for (const FIngredient& ingredient : Ingredients) {
		inv->removeItem(ingredient.Item, ingredient.Quantity, false);
	}
	inv->createItem(OutputItem, OutputQuantity);
}

bool URecipe::canMake(UInventory* inv) const
{
	
	for (const FIngredient& ingredient : Ingredients) {
		if (inv->hasItem(ingredient.Item, ingredient.Quantity) ) {
			return false;
		}
	}
	return true;
}
