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
	/** HomeLocation Ű ���� */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HomeLocationKey;

	/** TargetLocation Ű ���� */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetLocationKey;

	/** ���� ���� (X, Y) �ݰ� */
	UPROPERTY(EditAnywhere, Category = "Patrol")
	float PatrolRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	float AcceptanceRadius = 5.0f;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void OnMoveCompleted(UBehaviorTreeComponent* BehaviorTreeComponent) override;

private:
	FDelegateHandle MoveDelegateHandle;
};
