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
    /** �½�ũ ���� */
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    /** ������ ���� ����� ��� Stay ���� */
    EBlackboardNotificationResult OnBlackboardValueChanged(const UBlackboardComponent& Blackboard, FBlackboard::FKey Key);

    /** �½�ũ�� �ߴܵ� ��� ȣ�� */
    void OnAbort(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
