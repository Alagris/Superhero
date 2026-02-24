// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ItemInstance.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincible = false;

	bool IsDead() {
		return Health <= 0;
	}

	virtual void Kill() {
		//ragdoll
		if (!IsDead()) {
			if (ACharacter* a = Cast<ACharacter>(GetOwner())) {
				a->GetMesh()->SetSimulatePhysics(true);
				a->GetCharacterMovement()->DisableMovement();
				
			}
			Health = 0;
		}
	}
	virtual void Revive() {
		if (IsDead()) {
			if (ACharacter* a = Cast<ACharacter>(GetOwner())) {
				a->GetMesh()->SetSimulatePhysics(false);
				a->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				
			}
			Health = MaxHealth;
		}
	}

	virtual void ReceiveHit(class AActor* projectile, AActor* shooter, UItemInstance* rangedWeapon, float hitSpeed, FVector NormalImpulse, const FHitResult& Hit) {
		if (!IsInvincible) {
			Health -= rangedWeapon->getDamageDealt(this, shooter, hitSpeed);
			if (Health <= 0) {
				Kill();
			}
		}
	}
};
