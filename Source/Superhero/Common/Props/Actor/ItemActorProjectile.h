// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActorStatic.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ItemActorProjectile.generated.h"

class UInventoryAndHealth;

UCLASS()
class SUPERHERO_API AItemActorProjectile : public AItemActorStatic
{
	GENERATED_BODY()
	


	UPROPERTY(SaveGame, Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> Movement;


	UPROPERTY()
	AActor* Shooter;
	
	UPROPERTY(SaveGame)
	UItemInstance* RangedWeapon;

public:	
	// Sets default values for this actor's properties
	AItemActorProjectile();
	double hitSpeed() const {
		return GetVelocity().Length();
	}
	UFUNCTION()
	void onProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual bool isProjectile() const override {
		return true;
	}
	inline void shoot(AActor* shooter, UItemInstance * rangedWeapon, FVector velocity, float gravity=0) {
		Shooter = shooter;
		RangedWeapon = rangedWeapon;
		Movement->Velocity = velocity;
		Movement->ProjectileGravityScale = gravity;
		Movement->SetUpdatedComponent(RootComponent);
		Mesh->OnComponentHit.AddUniqueDynamic(this, &AItemActorProjectile::onProjectileHit);
		
	}


	static AItemActorProjectile* spawn(UWorld * world, UItemInstance* item, FTransform trans) {
		AItemActorProjectile* a = world->SpawnActor<AItemActorProjectile>(AItemActorProjectile::StaticClass(), trans);
		a->setItem(item);
		return a;
	}
	

};
