// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "NameComponent.h"
#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UDialogueComponent : public UNameComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TSoftObjectPtr<class UDialogueStage> DialogueStage;

	ACharacter* character;
	
	virtual void DialogueEntered(APlayerController* player) {};

	virtual void DialogueExited(APlayerController* player) {};

	virtual void PlayDialogueAnim(UAnimMontage* anim) {
		if (ACharacter* a = Cast<ACharacter>(GetOwner())) {
			a->GetMesh()->PlayAnimation(anim, false);
		}
	}
};
