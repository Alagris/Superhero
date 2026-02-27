// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Props/Furniture/Chest.h"
#include <Common/UI/GameHUD.h>
#include <Common/Inventory/NameComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Inv = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	Name = CreateDefaultSubobject<UNameComponent>(TEXT("Name"));
	Name->CharacterName = FText::FromString("Chest");
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChest::OnClose(UInventoryMenu* menu)
{
	if (IsValid(ClosingSound)) {
		UGameplayStatics::PlaySoundAtLocation(this, ClosingSound, GetActorLocation());
	}
}

void AChest::OnOpen(UInventoryMenu* menu)
{
	if (IsValid(OpeningSound)) {
		UGameplayStatics::PlaySoundAtLocation(this, OpeningSound, GetActorLocation());
	}
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChest::OnInteract_Implementation(AActor* actor, UItemInstance* item, const FHitResult& Hit)
{
	if (APawn* p = Cast<APawn>(actor)) {
		if (APlayerController* c = Cast<APlayerController>(p->GetController())) {
			if (AGameHUD * hud = Cast<AGameHUD>(c->GetHUD())) {
				if (UInventory* i = p->GetComponentByClass<UInventory>()) {
					if (UInventoryMenu* invMenu = hud->showInventoryMenu(i, Inv, true, EInventoryPage::NPC)) {
						OnOpen(invMenu);
						invMenu->OnInventoryCloseSignature.AddUObject(this, &AChest::OnClose);
					}
				}
			}
		}
	}
	
}

