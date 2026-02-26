// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "DialogueResponseListView.h"
#include "Dialogue.generated.h"

class UDialogueStage;
class IDialogueActor;
class AGameHUD;
/**
 * 
 */
UCLASS()
class SUPERHERO_API UDialogue : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
public:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void setup(AGameHUD* HUD, APlayerController* PlayerController, UDialogueComponent* Npc, TSoftObjectPtr<UDialogueStage> Stage=nullptr);


	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpeakerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpeakerText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UDialogueResponseListView* ResponseOptions;

	UPROPERTY()
	AGameHUD* HUD;

	inline void showText(FText text) {
		SpeakerText->SetText(text);
	}
	inline void showLine(FText name, FText text) {
		SetVisibility(ESlateVisibility::Visible);
		SpeakerName->SetText(name);
		showText(text);
	}
	inline void clearOptions() {
		ResponseOptions->ClearListItems();
	}
	inline bool hasOptions() const {
		return ResponseOptions->GetNumItems() > 0;
	}

	void closeDialogue();

	void followUp(TSoftObjectPtr<UDialogueStage> Stage);
};
