// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Core/AIControllerBase.h"
#include "NPCAIController.generated.h"

UENUM(Blueprintable)
enum class ENPCStates : uint8
{
	None	UMETA(Hidden),

	Stay			UMETA(DisplayName = "Stay"),			// Idle

	Wait			UMETA(DisplayName = "Wait"),			// Move
	MoveToPoint		UMETA(DisplayName = "MoveToPoint"),		// Move
	RoamToPoints	UMETA(DisplayName = "RoamToPoints"),	// Move
	Chase			UMETA(DisplayName = "Chase"),			// Move
	Return			UMETA(DisplayName = "Return"),			// Move

	Size    UMETA(Hidden)
};

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API ANPCAIController : public AAIControllerBase
{
	GENERATED_BODY()

/***** Functions (Unreal) *****/
public:
	ANPCAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;



private:
	// AI ป๓ลย
	ENPCStates NPCState = ENPCStates::None;

public:
	ENPCStates GetNPCState() const;
	void SetNPCState(ENPCStates NewNPCState);




/***** Functions (Task) *****/


private:
	UFUNCTION()
	void OnStayCompleted();
	UFUNCTION()
	void OnMoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	UFUNCTION()
	void OnRoamToPointReached(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	
};
