// Fill out your copyright notice in the Description page of Project Settings.


#include "Factions.h"


#if WITH_EDITOR
void UFactions::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property != NULL)
	{
		const FName& PropertyName = PropertyChangedEvent.GetMemberPropertyName();

		if (PropertyName == "Friends")
		{
			updateFriends();
		}
		if (PropertyName == "Enemies")
		{
			updateEnemies();
		}
	}
}
#endif