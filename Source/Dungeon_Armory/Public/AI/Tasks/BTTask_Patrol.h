// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Navigation/PathFollowingComponent.h"  // EPathFollowingResult Æ÷ÇÔ

#include "BTTask_Patrol.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class DUNGEON_ARMORY_API UBTTask_Patrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

/***** Variables *****/
private:
	UBehaviorTreeComponent* BehaviorTreeCmpt;

/***** Functions *****/
public:
	UBTTask_Patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

};
