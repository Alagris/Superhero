// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Props/Furniture/Chest.h"
#include "ChestSkeletal.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHERO_API AChestSkeletal : public AChest
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimationAsset* OpeningAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimationAsset* ClosingAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpeningPlayRate=1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ClosingPlayRate = 1;


	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

	AChestSkeletal();

	virtual void OnClose(class UInventoryMenu* menu) override;
	virtual void OnOpen(class UInventoryMenu* menu) override;
};
