// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInstance.h"
#include "ISpudObject.h"
#include "Inventory.generated.h"

class UClothingItem;


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemAddedSignature, class UItemInstance* /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemRemovedSignature, class UItemInstance* /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnItemEquippedSignature, const UClothingItem * /*type*/, class UItemInstance* /*item*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnItemConsumedSignature, class UItemInstance* /*item*/, int /*consumedCount*/, class UInventory* /* inventory */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClearInventorySignature, class UInventory * /* inventory */);


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
	UPROPERTY(SaveGame)
	bool isLootInitialized=false;
public:	
	
	bool EnsureLootInitialized();

	virtual void SpudStoreCustomData(const USpudState* State, USpudStateCustomData* CustomData) {
		CustomData->WriteInt(Items.Num());

		for (auto entry : Items) {
			UItemInstance* item = entry.Value;
			item->store(this, State, CustomData);
		}
	}

	virtual void SpudRestoreCustomData(USpudState* State, USpudStateCustomData* CustomData) {
		clearInventory();
		int count = 0;
		bool b = CustomData->ReadInt(count);
		check(b);
		UWorld* w = GetWorld();
		for (int i = 0; i < count; i++) {
			TObjectPtr<UItemInstance> item = NewObject<UItemInstance>(w, UItemInstance::StaticClass());
			item->restore(this, State, CustomData);
		}
		
	}

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<const UItem*, UItemInstance*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	class ULoot* Loot;

	FOnItemAddedSignature ItemAddedListeners;

	FOnItemRemovedSignature ItemRemovedListeners;

	FOnItemEquippedSignature ItemEquippedListeners;

	FOnItemEquippedSignature ItemUnequippedListeners;

	FOnItemConsumedSignature ItemConsumedListeners;

	FOnClearInventorySignature ClearListeners;

	UFUNCTION(BlueprintCallable)
	void addItem(UItemInstance* item);

	UFUNCTION(BlueprintCallable)
	UItemInstance* spawnItem(const UItem* itemType, int quantity);

	UItemInstance* removeItem(UItemInstance* item);

	UFUNCTION(BlueprintCallable)
	UItemInstance* removeItem(const UItem* item, int quantity=1, bool spawnPopped=true);


	UFUNCTION(BlueprintCallable)
	UItemInstance* useItem(const UItem* item, int quantity);

	void clearInventory();
	void resetInventory();
};
