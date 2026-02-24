// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActorNiagaraProjectile.h"
#include "NiagaraFunctionLibrary.h"
#include <Common/Interact/Hittable.h>

AItemActorNiagaraProjectile::AItemActorNiagaraProjectile()
{

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetMobility(EComponentMobility::Movable);
	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetEnableGravity(false);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->OnComponentHit.AddUniqueDynamic(this, &AItemActorNiagaraProjectile::onProjectileHit);
	//Mesh->RegisterComponent();
	//Mesh->SetupAttachment(RootComponent);
	SetRootComponent(CollisionSphere);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	Movement->bShouldBounce = false;
	Movement->ProjectileGravityScale = 0;
	//Movement->Bounciness = 0.1f;
	Movement->Friction = 0.5f;
	Movement->InitialSpeed = 1000.0;
	Movement->MaxSpeed = 10000.0;
	Movement->UpdatedComponent = RootComponent;
	
	
	
	
}

void AItemActorNiagaraProjectile::onProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (OtherActor == Shooter) {
	//	return;
	//}
	if (OtherActor != nullptr && OtherActor->Implements<UHittable>()) {

		IHittable::Execute_OnHit(OtherActor, this, Shooter, RangedWeapon, (float)hitSpeed(), NormalImpulse, Hit);
	}
	else {
		CollisionSphere->OnComponentHit.Clear();
	}

	if (Impact != nullptr) {
		UNiagaraComponent* n = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			Impact,
			Hit.Location,
			GetActorRotation()
		);
	}
	Destroy();
}

void AItemActorNiagaraProjectile::shoot(AActor* shooter, UItemInstance* rangedWeapon, FVector velocity, float gravity, UNiagaraSystem* fire) {
	Shooter = shooter;
	RangedWeapon = rangedWeapon;
	Movement->SetVelocityInLocalSpace(velocity);
	Movement->InitialSpeed = velocity.Length();
	Movement->ProjectileGravityScale = gravity;
	//Movement->SetUpdatedComponent(RootComponent);
	
	if (fire != nullptr) {
		UNiagaraComponent* n = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			fire,
			GetActorLocation(),
			GetActorRotation()
		);
	}
}

AItemActorNiagaraProjectile* AItemActorNiagaraProjectile::spawn(UWorld* world, UNiagaraSystem* trail, FTransform trans, UNiagaraSystem* impact)
{
	AItemActorNiagaraProjectile* a = world->SpawnActor<AItemActorNiagaraProjectile>(AItemActorNiagaraProjectile::StaticClass(), trans);
	a->Impact = impact;
	if (IsValid(trail)) {
		a->TrailComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(trail, a->RootComponent, NAME_None, FVector(), FRotator(), EAttachLocation::Type::SnapToTarget, false, true);
	}
	return a;
}
