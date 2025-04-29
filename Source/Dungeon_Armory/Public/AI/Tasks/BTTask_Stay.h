// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Stay.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API UBTTask_Stay : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_Stay();

protected:
    /** 태스크 실행 */
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    /** 블랙보드 값이 변경될 경우 Stay 종료 */
    EBlackboardNotificationResult OnBlackboardValueChanged(const UBlackboardComponent& Blackboard, FBlackboard::FKey Key);

    /** 태스크가 중단될 경우 호출 */
    void OnAbort(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
