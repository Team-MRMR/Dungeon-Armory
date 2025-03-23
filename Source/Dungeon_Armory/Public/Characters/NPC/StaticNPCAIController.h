// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPC/NPCAIController.h"
#include "StaticNPCAIController.generated.h"

UCLASS()
class DUNGEON_ARMORY_API AStaticNPCAIController : public ANPCAIController
{
	GENERATED_BODY()

/***** Functions (Unreal) *****/
public:
	AStaticNPCAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the controller possess a Pawn
	virtual void OnPossess(APawn* InPawn) override;

/***** Functions (Behavior Tree) *****/
private:
	UFUNCTION()
	void OnStayCompleted();

	UFUNCTION()
	void OnMoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	
};
