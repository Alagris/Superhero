// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "DoorNavLinkProxy.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API ADoorNavLinkProxy : public ANavLinkProxy
{
	GENERATED_BODY()
	
	ADoorNavLinkProxy();

	void NotifySmartLinkReached(UNavLinkCustomComponent* LinkComp, UObject* PathingAgent, const FVector& DestPoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class ADoor * Door;
	//void ReceiveSmartLinkReached(AActor* Agent, const FVector& Destination);
};
