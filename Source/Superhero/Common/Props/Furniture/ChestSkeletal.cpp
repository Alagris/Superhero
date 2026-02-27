// Fill out your copyright notice in the Description page of Project Settings.


#include "ChestSkeletal.h"
#include "Anim/OpenableFurnitureAnimInstance.h"

// Sets default values
AChestSkeletal::AChestSkeletal()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetMobility(EComponentMobility::Static);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	//Mesh->RegisterComponent();
	SetRootComponent(Mesh);

}

void AChestSkeletal::OnClose(UInventoryMenu* menu)
{
	Super::OnClose(menu);
	if (IsValid(ClosingAnim)) {
		//Mesh->SetPlayRate(ClosingPlayRate);
		Mesh->PlayAnimation(ClosingAnim, false);
		Mesh->SetPlayRate(ClosingPlayRate);
	}
}

void AChestSkeletal::OnOpen(UInventoryMenu* menu)
{
	Super::OnOpen(menu);
	if (IsValid(OpeningAnim)) {
		//Mesh->SetPlayRate(OpeningPlayRate);
		Mesh->PlayAnimation(OpeningAnim, false);
		Mesh->SetPlayRate(OpeningPlayRate);
	}
}