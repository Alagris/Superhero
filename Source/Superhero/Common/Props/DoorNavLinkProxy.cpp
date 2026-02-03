// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Props/DoorNavLinkProxy.h"
#include "NavLinkCustomComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Door.h"

ADoorNavLinkProxy::ADoorNavLinkProxy()
{
	PointLinks.Empty();
	bSmartLinkIsRelevant = true;
	GetSmartLinkComp()->SetMoveReachedLink(this, &ADoorNavLinkProxy::NotifySmartLinkReached);

}

void ADoorNavLinkProxy::NotifySmartLinkReached(UNavLinkCustomComponent* LinkComp, UObject* PathingAgent, const FVector& DestPoint)
{

	if (IsValid(Door)) {
		Door->Open();
	}
}
