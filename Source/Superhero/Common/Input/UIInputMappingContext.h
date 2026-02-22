// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Input/EnhancedInputMappingContext.h"
#include "UIInputMappingContext.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API UUIInputMappingContext : public UEnhancedInputMappingContext
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UInputAction* Up;

	UPROPERTY()
	UInputAction* Down;

	UPROPERTY()
	UInputAction* Left;

	UPROPERTY()
	UInputAction* Right;

	UPROPERTY()
	UInputAction* Exit;

	UPROPERTY()
	UInputAction* Enter;

	UPROPERTY()
	UInputAction* Interact;

	UPROPERTY()
	UInputAction* Drop;

	UPROPERTY()
	UInputAction* Inventory;

	UPROPERTY()
	UInputAction* Scroll;

	

	virtual void initialize(APlayerController* c) override {
		Up = mapPressKey(c, EKeys::Up,true);
		Down = mapPressKey(c, EKeys::Down, true);
		Left = mapPressKey(c, EKeys::Left, true);
		Right = mapPressKey(c, EKeys::Right, true);
		Exit = mapPressKey(c, EKeys::Escape, true);
		Enter = mapPressKey(c, EKeys::Enter, true);
		Interact = mapPressKey(c, EKeys::E, true);
		Drop = mapPressKey(c, EKeys::R, true);
		Inventory = mapPressKey(c, EKeys::C, true);
		Scroll = makeZoomAction(c);
		

	}
	
	virtual void setMapping(APlayerController* c)override {
		if (Up == nullptr) {
			initialize(c);
		}
		Super::setMapping(c);
	}
};
