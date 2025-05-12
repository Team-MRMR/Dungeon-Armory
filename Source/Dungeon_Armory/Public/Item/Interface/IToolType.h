// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IToolType.generated.h"

UENUM(BlueprintType)
enum class EToolType : uint8
{
	Other    UMETA(DisplayName = "Other"),

	//Weapon   UMETA(DisplayName = "Weapon"),
	Axe      UMETA(DisplayName = "Axe"),
	Pickaxe  UMETA(DisplayName = "Pickaxe")
};

// ���� ������ ToolType�� �������� �������̽�
UINTERFACE(MinimalAPI)
class UIToolType : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEON_ARMORY_API IIToolType
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	EToolType GetToolType() const;

	virtual EToolType GetToolType_Implementation() const = 0; // ���� ���� �Լ�
};
