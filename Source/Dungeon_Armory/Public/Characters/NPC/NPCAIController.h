// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPC/NPCAIControllerBase.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API ANPCAIController : public ANPCAIControllerBase
{
	GENERATED_BODY()

/***** Functions (Unreal) *****/
public:
	ANPCAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

/***** Functions (Task) *****/
private:
	UFUNCTION()
	void OnStayCompleted();
	UFUNCTION()
	void OnMoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	UFUNCTION()
	void OnRoamToPointReached(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	
};
