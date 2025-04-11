// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"

#include "Characters/Mannequin/ViewMode/ViewModeComponent.h"

#include "CameraTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API ACameraTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:
    ACameraTriggerVolume();

protected:
	virtual void BeginPlay() override;

/***** View Mode *****/

protected:
    UPROPERTY(EditAnywhere, Category = "ViewMode")
    EViewMode ViewModeToApply = EViewMode::FPS;

protected:
    UFUNCTION()
    void HandleTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
