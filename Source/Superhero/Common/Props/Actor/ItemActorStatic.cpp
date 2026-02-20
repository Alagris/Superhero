// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActorStatic.h"


// Sets default values
AItemActorStatic::AItemActorStatic()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetSimulatePhysics(true);
	//Mesh->RegisterComponent();
	//Mesh->SetupAttachment(RootComponent);
	SetRootComponent(Mesh);

}

