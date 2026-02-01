// Fill out your copyright notice in the Description page of Project Settings.


#include "Indoors/IndoorsPlayerController.h"
#include "Indoors/IndoorsPawn.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

AIndoorsPlayerController::AIndoorsPlayerController() {
	bShowMouseCursor = true;
}

UInputAction* AIndoorsPlayerController::MapKey(UInputMappingContext* ctx, FKey key, EInputActionValueType type, bool triggerWhenPaused) {
	UInputAction* act = NewObject<UInputAction>(this);
	act->bTriggerWhenPaused = triggerWhenPaused;
	act->ValueType = type;
	ctx->MapKey(act, key);
	return act;
}

void AIndoorsPlayerController::MapKey(UInputMappingContext* ctx, UInputAction* act, FKey key, bool negateX, bool negateY, bool negateZ) {
	FEnhancedActionKeyMapping& mapping = ctx->MapKey(act, key);
	UObject* outer = ctx->GetOuter();

	UInputModifierNegate* neg = NewObject<UInputModifierNegate>(outer);
	neg->bX = negateX;
	neg->bY = negateY;
	neg->bZ = negateZ;
	mapping.Modifiers.Add(neg);
}
void AIndoorsPlayerController::MapKey(UInputMappingContext* ctx, UInputAction* act, FKey key, bool negate, bool swizzle, EInputAxisSwizzle order) {
	FEnhancedActionKeyMapping& mapping = ctx->MapKey(act, key);
	UObject* outer = ctx->GetOuter();
	if (negate) {
		UInputModifierNegate* neg = NewObject<UInputModifierNegate>(outer);
		mapping.Modifiers.Add(neg);
	}
	if (swizzle) {
		UInputModifierSwizzleAxis* sw = NewObject<UInputModifierSwizzleAxis>(outer);
		sw->Order = order;
		mapping.Modifiers.Add(sw);
	}
}
UInputAction* AIndoorsPlayerController::MapTapKey(UInputMappingContext* ctx, FKey key, float timeThreshold) {
	UInputAction* act = NewObject<UInputAction>(this);
	FEnhancedActionKeyMapping& mapping = ctx->MapKey(act, key);
	UObject* outer = ctx->GetOuter();
	UInputTriggerTap* tap = NewObject<UInputTriggerTap>(outer);
	tap->TapReleaseTimeThreshold = timeThreshold;
	mapping.Triggers.Add(tap);
	return act;
}
void AIndoorsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	DefaultMappingContext = NewObject<UInputMappingContext>(this);

	LookAction = NewObject<UInputAction>(this);
	LookAction->ValueType = EInputActionValueType::Axis2D;
	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	
	MapKey(DefaultMappingContext, MoveAction, EKeys::D, false, true, EInputAxisSwizzle::YXZ);
	MapKey(DefaultMappingContext, MoveAction, EKeys::Right, false, true, EInputAxisSwizzle::YXZ);
	MapKey(DefaultMappingContext, MoveAction, EKeys::A, true, true, EInputAxisSwizzle::YXZ);
	MapKey(DefaultMappingContext, MoveAction, EKeys::Left, true, true, EInputAxisSwizzle::YXZ);
	MapKey(DefaultMappingContext, MoveAction, EKeys::S, true);
	MapKey(DefaultMappingContext, MoveAction, EKeys::Down, true);
	MapKey(DefaultMappingContext, MoveAction, EKeys::W);
	MapKey(DefaultMappingContext, MoveAction, EKeys::Up);
	MapKey(DefaultMappingContext, MoveAction, EKeys::SpaceBar, false, true, EInputAxisSwizzle::ZYX);
	MapKey(DefaultMappingContext, MoveAction, EKeys::LeftControl, true, true, EInputAxisSwizzle::ZYX);



	MapKey(DefaultMappingContext, LookAction, EKeys::Mouse2D, false, true, false);
	LeftClick = MapKey(DefaultMappingContext, EKeys::LeftMouseButton);
	RightClick = MapKey(DefaultMappingContext, EKeys::RightMouseButton);
	SetMapping(DefaultMappingContext);
}

void AIndoorsPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AIndoorsPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	GameCharacter = Cast<AIndoorsPawn>(InPawn);
	if (GameCharacter) {
		GameCharacter->OnPossessed(this);
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
			EnhancedInputComponent->BindAction(LeftClick, ETriggerEvent::Triggered, GameCharacter, &AIndoorsPawn::LeftClick);
			EnhancedInputComponent->BindAction(RightClick, ETriggerEvent::Started, this, &AIndoorsPlayerController::StartRightClick);
			EnhancedInputComponent->BindAction(RightClick, ETriggerEvent::Completed, this, &AIndoorsPlayerController::EndRightClick);
			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, GameCharacter, &AIndoorsPawn::Move);

			// Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIndoorsPlayerController::Look);
		}
	}

}
void AIndoorsPlayerController::SetMapping(UInputMappingContext* ctx)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(ctx, 0);
	}
}

void AIndoorsPlayerController::Look(const FInputActionValue& Value)
{
	if (isHoldingRMB) {
		// input is a Vector2D
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		if (LookAxisVector.X != 0.f)
		{
			AddYawInput(LookAxisVector.X);
		}
		if (LookAxisVector.Y != 0.f)
		{
			AddPitchInput(LookAxisVector.Y);
		}
	}
}


