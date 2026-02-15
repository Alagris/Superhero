// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootItemChance.generated.h"

class ULoot;
USTRUCT(BlueprintType)
struct FLootItemChance {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<ULoot> Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Likelihood=1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AccumulativeLikelihood = 1;

	inline bool operator<(const float p) const {
		return AccumulativeLikelihood < p;
	}
	inline bool operator<=(const float p) const {
		return AccumulativeLikelihood <= p;
	}
	inline 	bool operator>(const float p) const {
		return AccumulativeLikelihood > p;
	}
	inline 	bool operator>=(const float p) const {
		return AccumulativeLikelihood >= p;
	}
	inline 	bool operator==(const float p) const {
		return AccumulativeLikelihood == p;
	}
	friend bool operator<(const float p, const FLootItemChance &  rhs) { 
		return p < rhs.AccumulativeLikelihood;
	}
	friend bool operator<=(const float p, const FLootItemChance& rhs) {
		return p <= rhs.AccumulativeLikelihood;
	}
	friend bool operator>(const float p, const FLootItemChance& rhs) {
		return p > rhs.AccumulativeLikelihood;
	}
	friend bool operator>=(const float p, const FLootItemChance& rhs) {
		return p >= rhs.AccumulativeLikelihood;
	}
};

