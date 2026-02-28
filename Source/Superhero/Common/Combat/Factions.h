// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Faction.h"
#include "Factions.generated.h"


USTRUCT(BlueprintType)
struct FFactionRelationship {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFaction * First;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFaction* Second;

};

UCLASS()
class SUPERHERO_API UFactions : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UFaction*> Factions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FFactionRelationship> Friends;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FFactionRelationship> Enemies;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	
#endif

	template<typename T>
	static void AddIfAbsent(TArray<T>& arr, T elem) {
		if (IsValid(elem) && !arr.Contains(elem)) {
			arr.Add(elem);
		}
	}
	void updateFriends() {
		ensureAllFactionsArePresent(Friends);
		for (UFaction* f : Factions) {
			f->Friends.Empty();
		}
		for (FFactionRelationship& r : Friends) {
			if (IsValid(r.First) && IsValid(r.Second)) {
				AddIfAbsent(r.First->Friends, r.Second);
				AddIfAbsent(r.Second->Friends, r.First);
			}
		}
	}

	void updateEnemies() {
		ensureAllFactionsArePresent(Enemies);
		for (UFaction* f : Factions) {
			f->Enemies.Empty();
		}
		for (FFactionRelationship& r : Enemies) {
			if (IsValid(r.First) && IsValid(r.Second)) {
				AddIfAbsent(r.First->Enemies, r.Second);
				AddIfAbsent(r.Second->Enemies, r.First);
			}
		}
	}

	
	void ensureAllFactionsArePresent(TArray<FFactionRelationship>& e) {
		for (FFactionRelationship & r : e) {
			AddIfAbsent(Factions, r.First);
			AddIfAbsent(Factions, r.Second);
		}
		for (int i = Factions.Num()-1; i >= 0; i--) {
			if (!IsValid(Factions[i])) {
				Factions.RemoveAtSwap(i);
			}
		}
		
	}
};

