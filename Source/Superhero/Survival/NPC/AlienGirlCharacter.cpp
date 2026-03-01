// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienGirlCharacter.h"

void AAlienGirlCharacter::BeginPlay() {
	Super::BeginPlay();
	USkeletalMeshComponent* m = GetMesh();
	for (int i = 0; i < m->GetNumMaterials();i++) {
		UMaterialInstanceDynamic* d = UMaterialInstanceDynamic::Create(m->GetMaterial(i), this);
		for (FBodyColor& c : BodyColors) {
			d->SetVectorParameterValue(c.MaterialColorParam, c.BodyColor);
		}
		
		m->SetMaterial(i, d);
	}
	//"Color_Paint_1"
}
