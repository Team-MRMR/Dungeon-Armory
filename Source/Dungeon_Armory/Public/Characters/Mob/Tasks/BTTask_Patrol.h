// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Interface/IMovableTask.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API UBTTask_Patrol : public UBTTask_BlackboardBase, public IIMovableTask
{
	GENERATED_BODY()
	
public:
	UBTTask_Patrol();

/***** Patrol *****/

protected:
	/** HomeLocation ≈∞ º±≈√ */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBkey_HomeLocation;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBkey_PatrolRadius;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBkey_AcceptableRadius;


/***** Task *****/
protected:
	virtual void InitializeFromAsset(UBehaviorTree& BehaviorTree) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:  // IIMovableTask
	void OnMoveCompleted(UBehaviorTreeComponent* BehaviorTreeComponent) override;
};
