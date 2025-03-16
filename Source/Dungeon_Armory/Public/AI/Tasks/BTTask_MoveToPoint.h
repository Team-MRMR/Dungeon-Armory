// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Navigation/PathFollowingComponent.h"  // EPathFollowingResult Æ÷ÇÔ

#include "BTTask_MoveToPoint.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class DUNGEON_ARMORY_API UBTTask_MoveToPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

/***** Variables *****/
private:
	UBehaviorTreeComponent* BehaviorTreeCmp;

/***** Functions *****/
public:
	UBTTask_MoveToPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
};
