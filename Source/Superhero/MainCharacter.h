// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Character/ThirdPerson/ThirdPersonCharacter.h"
#include "Common/UI/Dialogue/DialogueActor.h"
#include "Common/Interact/Interactable.h"
#include <Common/Inventory/ClothingSystem.h>
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API AMainCharacter : public AThirdPersonCharacter, public IDialogueActor, public ISpudObject
{
	GENERATED_BODY()
public:
	AMainCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class UDialogueStage> DialogueStage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UClothingSystem* ClothingSys;


	virtual void OnDialogueEntered_Implementation(APlayerController* Player) override;

	virtual void OnDialogueExited_Implementation(APlayerController* Player) override;

	virtual FText GetCharacterName_Implementation() override {
		return CharacterName;
	}

	virtual void OnPlayDialogueAnim_Implementation(UAnimMontage* Anim) override;
	
};
