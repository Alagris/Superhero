// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISpudObject.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include <Common/Inventory/ClothingSystem.h>
#include "IndoorsSuperhero.generated.h"


class UClothingItem;

UCLASS()
class SUPERHERO_API AIndoorsSuperhero : public ACharacter, public ISpudObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIndoorsSuperhero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	//UPROPERTY()
	//TArray<TObjectPtr<USkeletalMeshComponent>> ClothesMeshes;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//TMap<UClothingItem, USkeletalMeshComponent>
	//
	//void destroySkeletalMeshComponent(USkeletalMeshComponent* comp);
	//USkeletalMeshComponent* createSkeletalMeshComponent(USkeletalMesh* mesh, bool allowOutline = true);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* BehaviourTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UClothingSystem* ClothingSys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UInventory* Inventory;
	

};
