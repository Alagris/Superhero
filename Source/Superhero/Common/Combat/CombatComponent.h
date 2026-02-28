// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackCombo.h"
#include <Common/Inventory/ClothingSystem.h>
#include <Common/Character/Movement/AdvancedMovementComponent.h>
#include "CombatComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	bool CanPlayNextAttack=true;
	class UAnimMontage* LastPlayerAttackMontage;
	bool WantsToAttack = false;
	bool WantsToAttackPrimary = false;
	bool WantsToAttackSecondary = false;


public:	
	// Sets default values for this component's properties
	UCombatComponent();
	virtual void InitializeComponent() override;

	
	
	UPROPERTY(BlueprintReadOnly)
	UClothingSystem* Clothing;
	
	UPROPERTY(BlueprintReadOnly)
	UAdvancedMovementComponent * Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAttackCombo* UnarmedCombo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, UAttackCombo*> Combos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAttackCombo* CurrentStartCombo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAttackCombo* CurrentExecutedCombo = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UItemInstance* CurrentWeapon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

	
	bool wantsToAttack() const {
		return WantsToAttack;
	}

	virtual void OnNextAttackReady() {
		if (wantsToAttack()) {
			ExecuteNextAttack(false);
		}
		else {
			CanPlayNextAttack = true;
		}
	}

	void ExecuteNextAttack(bool isHeavy);

	

	UAttackCombo* getCombo(FName id) const{
		return Combos.FindRef(id, UnarmedCombo);
	}



	void setNotWantsToAttack() {
		WantsToAttack = false;
		CurrentWeapon = nullptr;
		CurrentStartCombo = nullptr;
		CurrentStartCombo = nullptr;
	}

	void setWantsToAttack(UItemInstance* instance, UAttackCombo* combo, bool isPrimary, bool isHeavy)
	{
		WantsToAttack = true;
		CurrentWeapon = instance;
		if (combo != CurrentStartCombo) {
			CurrentExecutedCombo = nullptr;
		}
		CurrentStartCombo = combo;
		if (CanPlayNextAttack || !isStillPlayingAttackAnim()) {
			ExecuteNextAttack(false);
		}
	}
	UItemInstance* attackStart(bool isPrimary, bool heavy) {
		UItemInstance* i = getEquippedInRightHand();
		if (i == nullptr) {
			if (isPrimary) {
				setWantsToAttack(nullptr, UnarmedCombo, isPrimary, heavy);
			}
		}
		else {
			i->attackStart(this, isPrimary, heavy);
		}
		return i;
	}
	UItemInstance* attackEnd(bool isPrimary, bool heavy) {
		UItemInstance* i = getEquippedInRightHand();
		if (i == nullptr) {
			if (isPrimary) {
				setNotWantsToAttack();
			}
		}
		else {
			i->attackEnd(this, isPrimary, heavy);
		}
		return i;
	}

	
	void endAiming() {
		if (IsValid(Movement)) {
			Movement->endAiming();
		}
	}
	bool IsAiming() {
		if (IsValid(Movement)) {
			return Movement->IsAiming;
		}
		return false;
	}
	void startAiming() {
		if (IsValid(Movement)) {
			Movement->startAiming();
		}
	}
	UItemInstance* getEquippedInLeftHand() {
		if (IsValid(Clothing)) {
			return Clothing->getEquippedInLeftHand();
		}
		return nullptr;
	}
	UItemInstance* getEquippedInRightHand() {
		if (IsValid(Clothing)) {
			return Clothing->getEquippedInRightHand();
		}
		return nullptr;
	}
	UItemInstance* attackPrimaryEnd(bool heavy) {
		WantsToAttackPrimary = false;
		return attackEnd(true, heavy);
	}
	UItemInstance* attackSecondaryEnd(bool heavy)  {
		WantsToAttackSecondary = false;
		return attackEnd(false, heavy);
	}
	UItemInstance* attackPrimaryStart(bool heavy)  {
		WantsToAttackPrimary = true;
		return attackStart(true, heavy);
	}
	UItemInstance* attackSecondaryStart(bool heavy)  {
		WantsToAttackSecondary = true;
		return attackStart(false, heavy);
	}

	void TriggerLeftAttackStart(const struct FInputActionValue& Value) {
		attackPrimaryStart(false);
	}
	void TriggerLeftAttackEnd(const struct FInputActionValue& Value) {
		attackPrimaryEnd(false);
	}
	void TriggerRightAttackStart(const struct FInputActionValue& Value) {
		attackSecondaryStart(false);
	}
	void TriggerRightAttackEnd(const struct FInputActionValue& Value) {
		attackSecondaryEnd(false);
	}
	bool isStillPlayingAttackAnim() {
		return IsPlayingAnimMontage(LastPlayerAttackMontage);
	}
	inline bool IsPlayingAnimMontage(class UAnimMontage* AnimMontage) {
		return getAnimInstance()->Montage_IsPlaying(AnimMontage);
	}
	inline float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1) {
		return getAnimInstance()->Montage_Play(AnimMontage, InPlayRate);
	}
	inline void StopAnimMontage(float InBlendOutTime, const UAnimMontage* Montage = 0) {
		getAnimInstance()->Montage_Stop(InBlendOutTime, Montage);
	}
	inline UAnimInstance* getAnimInstance() const {
		return Mesh->GetAnimInstance();
	}
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void Attack(AActor* target = nullptr) {
	}
};
