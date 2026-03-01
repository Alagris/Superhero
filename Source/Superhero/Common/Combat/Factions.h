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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ETeamAttitude::Type> Attitude;

};

UCLASS()
class SUPERHERO_API UFactions : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UFaction*> Factions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FFactionRelationship> Attitudes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<ETeamAttitude::Type>> AttitueMatrix;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	
#endif
	int getSymmetricalIndex(FFactionRelationship& r) {
		return getIndex(r.Second, r.First);
	}
	int getIndex(FFactionRelationship& r) {
		return getIndex(r.First, r.Second);
	}
	int getIndex(UFaction* a, UFaction* b) {
		return getIndex(a->FactionIndex, b->FactionIndex);
	}
	int getIndex(int a,int b) {
		return a * Factions.Num() + b;
	}
	void AddIfAbsent(UFaction * fac) {
		if (IsValid(fac) && !Factions.Contains(fac)) {
			Factions.Add(fac);
		}
	}
	void update() {
		for (FFactionRelationship& r : Attitudes) {
			AddIfAbsent(r.First);
			AddIfAbsent(r.Second);
		}
		for (int i = Factions.Num() - 1; i >= 0; i--) {
			if (!IsValid(Factions[i])) {
				Factions.RemoveAtSwap(i);
			}
		}
		for (int i = 0; i < Factions.Num();i++) {
			Factions[i]->FactionIndex = i;
			Factions[i]->TeamId = i;
			Factions[i]->Owner = this;
		}
		AttitueMatrix.Empty();
		for (int i = 0; i < Factions.Num() * Factions.Num(); i++) {
			AttitueMatrix.Add(ETeamAttitude::Neutral);
		}
		for (int i = 0; i < Factions.Num() ; i++) {
			AttitueMatrix[getIndex(i,i)] = ETeamAttitude::Friendly;
		}
		for (int i = 0; i < Attitudes.Num(); i++) {
			FFactionRelationship & r = Attitudes[i];
			int idx = getIndex(r);
			AttitueMatrix[idx] = r.Attitude;
			idx = getSymmetricalIndex(r);
			AttitueMatrix[idx] = r.Attitude;
		}
		
	}

	ETeamAttitude::Type getAttitude(UFaction* a, UFaction* b) {
		if (IsValid(b) && IsValid(a)) {
			return AttitueMatrix[getIndex(a,b)];
		}
		return ETeamAttitude::Neutral;
	}
	
};

