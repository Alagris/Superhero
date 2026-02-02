// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "IndexedListView.generated.h"

UCLASS()
class SUPERHERO_API UIndex : public UObject
{
	GENERATED_BODY()

public:
	int idx;

};
/**
 * 
 */
UCLASS()
class SUPERHERO_API UIndexedListView : public UListView
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<UIndex>> IndexCache;
public:
	void reserve(int optionCount) {
		while (IndexCache.Num() < optionCount) {
			UIndex* idx = NewObject<UIndex>(this);
			idx->idx = IndexCache.Num();
			IndexCache.Add(idx);
		}
	}
	void appendOption(int optionIdx) {
		reserve(optionIdx + 1);
		addOption(optionIdx);
	}
	void addOption(int optionIdx) {
		AddItem(IndexCache[optionIdx]);
	}
	void setNum(int optionCount) {
		reserve(optionCount);
		ClearListItems();
		for (int i = 0; i < optionCount; i++) {
			addOption(i);
		}

	}
	void removeOption(int idx) {
		UIndex* idxObj = IndexCache[idx];
		RemoveItem(idxObj);
		IndexCache.RemoveAt(idx);
		for (int i = idx; i < IndexCache.Num(); i++) {
			IndexCache[i]->idx = i;
		}
	}

};
