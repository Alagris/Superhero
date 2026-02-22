// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyMesh.h"

UPrimitiveComponent* FAnyMesh::findSocket(FVector& location, FRotator& rotation, const FName itemSocket){
	location = FVector();
	rotation = FRotator();
	if (isSkeletal) {
		if (skeletal != nullptr) {
			USkeletalMesh* const itemMesh = skeletal->GetSkeletalMeshAsset();
			if (itemMesh) {
				const USkeletalMeshSocket* const socket = itemMesh->FindSocket(itemSocket);
				if (socket) {
					location = socket->RelativeLocation;
					rotation = socket->RelativeRotation;
				}
			}
		}
		return skeletal;
	}
	else {
		if (ztatic != nullptr) {
			UStaticMesh* const itemMesh = ztatic->GetStaticMesh();
			if (itemMesh) {
				const UStaticMeshSocket* const socket = itemMesh->FindSocket(itemSocket);
				if (socket) {
					location = socket->RelativeLocation;
					rotation = socket->RelativeRotation;
				}
			}
		}
		return ztatic;
	}
}
UPrimitiveComponent* FAnyMesh::findSocketInverted(FVector& location, FRotator& rotation, const FName itemSocket) {
	UPrimitiveComponent*  i = findSocket(location, rotation, itemSocket);
	location = -location;
	rotation = rotation.GetInverse();
	return i;
}