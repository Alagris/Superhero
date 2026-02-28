// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

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
			LastPlayerAttackMontage = CurrentExecutedCombo->AttackAnim;
			if (IsValid(LastPlayerAttackMontage)) {
				CanPlayNextAttack = false;
				PlayAnimMontage(LastPlayerAttackMontage);
				return;
			}
		}
		setNotWantsToAttack();
	}
}
void UCombatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	Clothing = GetOwner()->GetComponentByClass<UClothingSystem>();
	Movement = GetOwner()->GetComponentByClass<UAdvancedMovementComponent>();
	if (ACharacter* c = Cast<ACharacter>(GetOwner())) {
		Mesh = c->GetMesh();
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

