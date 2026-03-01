// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "Common/Combat/CombatComponent.h"

AEnemyAICharacter::AEnemyAICharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer) {
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
}

