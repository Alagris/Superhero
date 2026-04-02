// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Common/AI/AIControlableComponent.h>
#include "ISpudObject.h"
#include "GenericTeamAgentInterface.h"
#include <Common/Interact/Hittable.h>
#include <Common/Combat/HasFactions.h>
#include <Common/Inventory/Health.h>
#include "BasicAICharacter.generated.h"


UCLASS(MinimalAPI)
class ABasicAICharacter : public ACharacter, public IHittable, public IHasFactions, public ISpudObject, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicAICharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static SUPERHERO_API FName FactionsComponentName;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UAIControlableComponent* AI;

	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UHealth* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UFactionsComponent* Factions;

	virtual UFactionsComponent* getFactionsComponent() const override {
		return Factions;
	}

	virtual void OnHit_Implementation(class AActor* projectile, AActor* shooter, class UItemInstance* rangedWeapon, float hitSpeed, FVector NormalImpulse, const FHitResult& Hit) override {
		Health->ReceiveHit(projectile, shooter, rangedWeapon, hitSpeed, NormalImpulse, Hit);
		
	}
	
	virtual FGenericTeamId GetGenericTeamId() const {
		return Factions->getTeamId();
	}
};
