// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
#include "TapOrHold.generated.h"

UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Tap Or Hold", NotInputConfigurable = "true"))
class UTapOrHold : public UInputTrigger
{
    GENERATED_BODY()

protected:
    virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
public:

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false"))
    float TapReleaseTimeThreshold = .5f;
    float HeldDuration = 0.0f;
};

