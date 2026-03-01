// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Common/AI/AIControlableComponent.h>
#include "ISpudObject.h"
#include "GenericTeamAgentInterface.h"
#include <Common/Interact/Hittable.h>
#include <Common/Inventory/Health.h>
#include "BasicAICharacter.generated.h"


UCLASS()
class SUPERHERO_API ABasicAICharacter : public ACharacter, public IHittable, public ISpudObject, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicAICharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	class UAIPerceptionComponent* Perception;
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	UHealth* Health;

	virtual void OnHit_Implementation(class AActor* projectile, AActor* shooter, class UItemInstance* rangedWeapon, float hitSpeed, FVector NormalImpulse, const FHitResult& Hit) override {
		Health->ReceiveHit(projectile, shooter, rangedWeapon, hitSpeed, NormalImpulse, Hit);
		
	}
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGenericTeamId TeamId = FGenericTeamId::NoTeam;

	virtual FGenericTeamId GetGenericTeamId() const {
		return TeamId;
	}
};
