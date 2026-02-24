// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISpudObject.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Common/Inventory/ItemInstance.h>
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "ItemActorNiagaraProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API AItemActorNiagaraProjectile : public AActor, public ISpudObject, public ISpudObjectCallback
{
	GENERATED_BODY()


public:

	UPROPERTY(SaveGame, Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* TrailComponent = nullptr;

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere;

	UPROPERTY(SaveGame, Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* Movement;


	AItemActorNiagaraProjectile();

	UPROPERTY()
	FGuid SpudGuid;

	UPROPERTY()
	AActor* Shooter;

	UPROPERTY(SaveGame)
	UItemInstance* RangedWeapon;

	virtual ESpudRespawnMode GetSpudRespawnMode_Implementation() const override { return ESpudRespawnMode::AlwaysRespawn; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame)
	UNiagaraSystem* Impact;

	UFUNCTION()
	void onProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	double hitSpeed() const {
		return GetVelocity().Length();
	}

	void shoot(AActor* shooter, UItemInstance* rangedWeapon, FVector velocity, float gravity = 0, UNiagaraSystem* fire=nullptr);


	static AItemActorNiagaraProjectile* spawn(UWorld* world, UNiagaraSystem* trail, FTransform trans, UNiagaraSystem* impact = nullptr);
};
