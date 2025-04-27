// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Core/AIControllerBase.h"
#include "MobAIController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API AMobAIController : public AAIControllerBase
{
	GENERATED_BODY()
	
/***** Unreal *****/
public:
	AMobAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

/***** AI *****/
protected:
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus) override;
};
