// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Mannequin/Component/ToolStatComponent.h"
#include "PickaxeStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API UPickaxeStatComponent : public UToolStatComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UPickaxeStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
