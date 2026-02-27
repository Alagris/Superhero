// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ISpudObject.h"
#include "Common/Interact/Interactable.h"
#include "Chest.generated.h"

UCLASS()
class SUPERHERO_API AChest : public AActor, public ISpudObject, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* OpeningSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* ClosingSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	class UInventory* Inv;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	class UNameComponent* Name;

	virtual void OnClose(class UInventoryMenu* menu);
	virtual void OnOpen(class UInventoryMenu* menu);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation(AActor* actor, class UItemInstance* item, const struct FHitResult& Hit) override;
};
