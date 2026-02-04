// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInstance.h"
#include "ISpudObject.h"
#include "Inventory.generated.h"

class UClothingItem;


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemAddedSignature, FItemInstance& /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemRemovedSignature, FItemInstance& /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnItemEquippedSignature, UClothingItem * /*type*/, FItemInstance& /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnItemConsumedSignature, FItemInstance& /*item*/, int /*consumedCount*/, class UInventory* /* inventory */);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UInventory : public UActorComponent, public ISpudObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	TMap<UItem*, FItemInstance> Items;

	FOnItemAddedSignature ItemAddedListeners;

	FOnItemRemovedSignature ItemRemovedListeners;

	FOnItemEquippedSignature ItemEquippedListeners;

	FOnItemEquippedSignature ItemUnequippedListeners;

	FOnItemConsumedSignature ItemConsumedListeners;

	UFUNCTION(BlueprintCallable)
	void addItem(UItem * item, int quantity);

	UFUNCTION(BlueprintCallable)
	void removeItem(UItem* item, int quantity);

	UFUNCTION(BlueprintCallable)
	void useItem(UItem* item, int quantity);
};
