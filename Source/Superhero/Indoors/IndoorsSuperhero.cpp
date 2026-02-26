// Fill out your copyright notice in the Description page of Project Settings.


#include "Indoors/IndoorsSuperhero.h"
#include "Indoors/IndoorsPlayerController.h"

// Sets default values
AIndoorsSuperhero::AIndoorsSuperhero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	ClothingSys = CreateDefaultSubobject<UClothingSystem>(TEXT("Clothing"));
	Dialogue = CreateDefaultSubobject<UDialogueComponent>(TEXT("Dialogue"));
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

}

// Called when the game starts or when spawned
void AIndoorsSuperhero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndoorsSuperhero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIndoorsSuperhero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIndoorsSuperhero::OnInteract_Implementation(AActor* actor, class UItemInstance* item, const struct FHitResult& Hit)
{
	if (AIndoorsPlayerController* player = Cast<AIndoorsPlayerController>(actor)) {
		player->OnSuperHeroSelected(this);
	}
	
}
