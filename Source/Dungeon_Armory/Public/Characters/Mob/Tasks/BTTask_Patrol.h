// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Interface/IMovableTask.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_Patrol.generated.h"

struct FBlackboardKeySelector;
class UMovementControllerComponent;

UCLASS()
class DUNGEON_ARMORY_API UBTTask_Patrol : public UBTTask_BlackboardBase, public IIMovableTask
{
	GENERATED_BODY()
	
public:
	UBTTask_Patrol();

/***** Patrol *****/
protected:
	/** HomeLocation Ű ���� */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBkey_HomeLocation;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBkey_PatrolRadius;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBkey_AcceptableRadius;

private:
	UMovementControllerComponent* MovementController;
	FNavLocation RandomLocation;
	float AcceptableRadius;

protected:
	virtual void InitializeFromAsset(UBehaviorTree& BehaviorTree) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


protected:  // IIMovableTask
	void OnMoveCompleted(UBehaviorTreeComponent* BehaviorTreeComponent) override;
};
