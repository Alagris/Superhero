// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ISpudObject.h"
#include "Common/Interact/Interactable.h"
#include "Door.generated.h"

UCLASS()
class SUPERHERO_API ADoor : public AActor, public ISpudObject, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	bool bIsOpen=false;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void OnClose();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void OnOpen();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Open() {
		if (!bIsOpen) {
			bIsOpen = true;
			OnOpen();
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Close() {
		if (bIsOpen) {
			bIsOpen = false;
			OnClose();
		}
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation(AActor* actor, class UItemInstance* item, const struct FHitResult& Hit) override {
		if (bIsOpen) {
			bIsOpen = false;
			OnClose();
		}
		else {
			bIsOpen = true;
			OnOpen();
		}
	}
};
