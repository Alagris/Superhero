// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISpudObject.h"
#include "Common/Character/Commander/CommandedCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Common/UI/Dialogue/DialogueActor.h"
#include "Common/Interact/Interactable.h"
#include <Common/Inventory/ClothingSystem.h>
#include "IndoorsSuperhero.generated.h"

class APlayerController;
class UClothingItem;

UCLASS()
class SUPERHERO_API AIndoorsSuperhero : public ACommandedCharacter, public ISpudObject, public IDialogueActor, public IInteractable
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class UDialogueStage> DialogueStage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UClothingSystem* ClothingSys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UInventory* Inventory;

	virtual void OnInteract_Implementation(AActor* actor, class UItemInstance* item, const struct FHitResult& Hit) override;
	
	virtual void OnDialogueEntered_Implementation(APlayerController* Player) override;

	virtual void OnDialogueExited_Implementation(APlayerController* Player) override;
	
	virtual FText GetCharacterName_Implementation() override {
		return CharacterName;
	}

	virtual void OnPlayDialogueAnim_Implementation(UAnimMontage* Anim) override;

};
