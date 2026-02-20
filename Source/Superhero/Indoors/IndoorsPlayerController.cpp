// Fill out your copyright notice in the Description page of Project Settings.


#include "Indoors/IndoorsPlayerController.h"
#include "Indoors/IndoorsPawn.h"
#include <EnhancedInputComponent.h>
#include "Common/Interact/Interactable.h"
#include "Common/UI/Dialogue/DialogueActor.h"
#include "Common/UI/Dialogue/DialogueStage.h"
#include <EnhancedInputSubsystems.h>
#include <Common/UI/GameHUD.h>
#include "IndoorsSuperhero.h"

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

UInputAction* AIndoorsPlayerController::MapPressedKey(UInputMappingContext* ctx, FKey key) {
	UInputAction* act = NewObject<UInputAction>(this);
	FEnhancedActionKeyMapping& mapping = ctx->MapKey(act, key);
	UObject* outer = ctx->GetOuter();
	UInputTriggerPressed* tap = NewObject<UInputTriggerPressed>(outer);
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
	LeftClick = MapPressedKey(DefaultMappingContext, EKeys::LeftMouseButton);
	RightClick = MapKey(DefaultMappingContext, EKeys::RightMouseButton);
	PauseGameAction = MapKey(DefaultMappingContext, EKeys::Escape, EInputActionValueType::Boolean, true);
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
			EnhancedInputComponent->BindAction(LeftClick, ETriggerEvent::Triggered, this, &AIndoorsPlayerController::OnLeftClick);
			EnhancedInputComponent->BindAction(RightClick, ETriggerEvent::Started, this, &AIndoorsPlayerController::StartRightClick);
			EnhancedInputComponent->BindAction(RightClick, ETriggerEvent::Completed, this, &AIndoorsPlayerController::EndRightClick);
			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, GameCharacter, &AIndoorsPawn::Move);

			// Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIndoorsPlayerController::Look);
			EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Started, this, &AIndoorsPlayerController::OnTriggerPauseGame);
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
		CumulativeLookAxisVector += LookAxisVector;
		if (abs(CumulativeLookAxisVector.X) > 0.01 || abs(CumulativeLookAxisVector.Y) > 0.01) {
			SetShowMouseCursor(false);
		}
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

void AIndoorsPlayerController::OnLeftClick(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Left click"));

	if (bShowMouseCursor) {
		FHitResult hit;
		if (GetHitResultUnderCursor(ECC_Visibility, true, hit)) {
			AActor * a = hit.GetActor();
			if (a!=nullptr && a->Implements<UInteractable>()) {
				IInteractable::Execute_OnInteract(a, this, nullptr, hit);
			}
		}
		
	}
}

void AIndoorsPlayerController::EndRightClick(const FInputActionValue& Value)
{
	isHoldingRMB = false;
	if (!bShowMouseCursor) {
		SetShowMouseCursor(true);
		if (IsValid(SelectedHero)) {
			FHitResult hit;
			if (GetHitResultUnderCursor(ECC_Visibility, true, hit)) {

			}
		}
	}
}

void AIndoorsPlayerController::TriggerPauseGame()
{
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		hud->triggerPauseGame(this);
	}	
}

bool AIndoorsPlayerController::PauseGame()
{
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		return hud->showPauseMenu(this);
	}
	return false;
}

bool AIndoorsPlayerController::UnpauseGame()
{
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		return hud->hidePauseMenu(this);
	}
	return false;
}

bool AIndoorsPlayerController::OpenDialogue(APlayerController* PlayerController, TScriptInterface<IDialogueActor> Npc, TSoftObjectPtr<UDialogueStage> Stage)
{
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		hud->showDialogue(PlayerController, Npc, Stage);
	}
	return false;

}
void AIndoorsPlayerController::OnSuperHeroSelected(AIndoorsSuperhero* hero)
{
	SelectedHero = hero;
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		hud->showCharacterMenu(this, hero);
	}
}
bool AIndoorsPlayerController::CloseDialogue()
{
	if (AGameHUD* hud = Cast<AGameHUD>(GetHUD())) {
		return hud->hideDialogue(this);		
	}
	return false;
}


