// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Common/UI/Status/HealthBarWidget.h"
#include "GameFramework/Character.h"
#include "ISpudObject.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ItemInstance.h"
#include <Components/WidgetComponent.h>
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHERO_API UHealth : public UActorComponent, public ISpudObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//virtual void InitializeComponent() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Health=100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Stamina = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float MaxStamina = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincible = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;

	UPROPERTY()
	UWidgetComponent* HealthBarComponent;

	UPROPERTY()
	UHealthBarWidget* HealthBar;

	bool IsDead() {
		return Health <= 0;
	}

	void Kill() {
		if (!IsDead()) {
			OnKill();
			Health = 0;
		}
	}
	virtual void OnKill() {
		//ragdoll
		
		if (ACharacter* a = Cast<ACharacter>(GetOwner())) {
			USkeletalMeshComponent * c = a->GetMesh();
			c->SetSimulatePhysics(true);
			a->GetCharacterMovement()->DisableMovement();
			
		}
		destroyHealthBar();
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

	void destroyHealthBar()
	{
		if (HealthBarComponent != nullptr) {
			HealthBarComponent->DestroyComponent();
			HealthBarComponent = nullptr;
			HealthBar = nullptr;
		}
	}
	void showHealthBar() {
		if (!IsValid(HealthBarComponent) && IsValid(HealthBarWidgetClass)) {
			check(HealthBar == nullptr);
			HealthBarComponent = NewObject<UWidgetComponent>(this, UWidgetComponent::StaticClass());
			HealthBarComponent->SetWidgetClass(HealthBarWidgetClass);
			FVector origin;
			FVector extent;
			GetOwner()->GetActorBounds(true, origin, extent, false);
			FVector2D size(extent.X + extent.Y, 30 + extent.Z * 2);
			HealthBarComponent->SetDrawSize(size);
			HealthBarComponent->InitWidget();
			HealthBarComponent->RegisterComponent();
			HealthBarComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			HealthBar = Cast<UHealthBarWidget>(HealthBarComponent->GetWidget());
			HealthBar->Health->SetPercent(getHealthPercent());
		}
		
	}

	float getHealthPercent() {
		return MaxHealth==0?1:Health / MaxHealth;
	}

	void damage(float hp) {
		if (!IsInvincible && Health>0) {
			Health -= hp;
			if (Health <= 0) {
				OnKill();
				Health = 0;
			}else {
				showHealthBar();
			}
		}
	}

	virtual void ReceiveHit(class AActor* projectile, AActor* shooter, UItemInstance* rangedWeapon, float hitSpeed, FVector NormalImpulse, const FHitResult& Hit) {
		if (!IsInvincible) {
			damage(rangedWeapon->getDamageDealt(this, shooter, hitSpeed));
		}
	}
};
