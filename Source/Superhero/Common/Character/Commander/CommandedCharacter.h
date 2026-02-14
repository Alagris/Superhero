// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CommandedCharacter.generated.h"

/**
 *  A controllable top-down perspective character
 */
UCLASS(abstract)
class ACommandedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* BehaviourTree;



};

