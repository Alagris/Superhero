// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EClothingSlot : uint8
{
	NONE = 0                              UMETA(DisplayName="NONE"), // 00000000 
	STOMACH = 1                           UMETA(DisplayName = "STOMACH"), // 00000001 
	HEAD = 2                              UMETA(DisplayName = "HEAD"), // 00000010 
	ASS = 4                               UMETA(DisplayName = "ASS"), // 00000100 
	ARMS = 8                              UMETA(DisplayName = "ARMS"), // 00001000 
	BREAST = 16                           UMETA(DisplayName = "BREAST"), // 00010000 
	FEET = 32                             UMETA(DisplayName = "FEET"), // 00100000 
	HANDS = 64                            UMETA(DisplayName = "HANDS"), // 01000000 
	LEGS = 128                            UMETA(DisplayName = "LEGS"), // 10000000 
	TOP = 1 + 16                          UMETA(DisplayName = "STOMACH+BREAST"),  
	LONG_TOP = 1 + 8 + 16                 UMETA(DisplayName = "STOMACH+BREAST+ARMS"),
	TORSO = 1+4+16                        UMETA(DisplayName = "ASS+STOMACH+BREAST"), // 00010101 
	UPPER = 1 + 4 + 8 + 16                UMETA(DisplayName = "ASS+STOMACH+BREAST+ARMS"), // 00011101 
	ARMS_HANDS = 8 + 64                   UMETA(DisplayName = "ARMS+HANDS"),
	BIKINI = 4 + 16                       UMETA(DisplayName = "ASS+BREAST"),
	LEGS_FEET = 32 + 128                  UMETA(DisplayName = "FEET+LEGS"),
	LOWER = 4 + 32 + 128                  UMETA(DisplayName = "FEET+LEGS+ASS"),
	NO_ARMS = 1 + 4 + 16 + 32 + 128       UMETA(DisplayName = "FEET+LEGS+ASS+STOMACH+BREAST"),
	NO_STOMACH = 4 + 16 + 32 + 128        UMETA(DisplayName = "FEET+LEGS+ASS+BREAST"),
	NO_STOMACH_ARMS = 4 + 8 + 16 + 32 + 128  UMETA(DisplayName = "FEET+LEGS+ASS+BREAST+ARMS"),
	FULL_BODY = 1 + 4 + 8+ 16 + 32 + 128  UMETA(DisplayName = "FEET+LEGS+ASS+STOMACH+BREAST+ARMS"),
	BODY_HEAD = 1 + 2 +4 + 8 + 16 + 32 + 128  UMETA(DisplayName = "FEET+LEGS+ASS+STOMACH+BREAST+ARMS+HEAD"),
	ALL = 255                            UMETA(DisplayName = "EVERYTHING"),
};