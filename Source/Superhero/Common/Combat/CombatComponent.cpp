// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "Common/Props/Projectiles/ProjectileType.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}

void UCombatComponent::ExecuteNextAttack(bool isHeavy)
{
	if (WantsToAttack ) {
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->attackTrigger(this, isHeavy);
		}
		if (CurrentExecutedCombo == nullptr) {
			CurrentExecutedCombo = CurrentStartCombo;
		}
		else {
			CurrentExecutedCombo = CurrentExecutedCombo->getNext(WantsToAttackPrimary, isHeavy);
		}
		if (IsValid(CurrentExecutedCombo)) {
			LastPlayedAttackMontage = CurrentExecutedCombo->AttackAnim;
			if (IsValid(LastPlayedAttackMontage)) {
				CanPlayNextAttack = false;
				PlayAnimMontage(LastPlayedAttackMontage);
				return;
			}
		}
		setNotWantsToAttack();
	}
}

void UCombatComponent::shootFromCharacterSocket(FName socket, UProjectileType* overwriteProjectile)
{
	if (overwriteProjectile == nullptr) {
		overwriteProjectile = UnarmedProjectile;
	}
	if(IsValid(overwriteProjectile)){
		overwriteProjectile->shootFromSkeletalSocket(socket, Mesh, nullptr, AutoAimTarget);
	}
}

void UCombatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	Clothing = GetOwner()->GetComponentByClass<UClothingSystem>();
	Movement = GetOwner()->GetComponentByClass<UAdvancedMovementComponent>();
	if (ACharacter* c = Cast<ACharacter>(GetOwner())) {
		Mesh = c->GetMesh();
		Mesh->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &UCombatComponent::OnAttackMontageEnd);
	}
	if (!IsValid(Mesh)) {
		check(false);
		DestroyComponent();
	}
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

