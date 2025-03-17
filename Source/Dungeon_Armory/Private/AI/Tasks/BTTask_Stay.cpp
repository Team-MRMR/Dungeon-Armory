// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Stay.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Manager/InGameTimeManager.h"

UBTTask_Stay::UBTTask_Stay()
{
    NodeName = "Stay";
}

EBTNodeResult::Type UBTTask_Stay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // ���� �ð� �Ŵ��� ã��
    UInGameTimeManager* TimeManager = UInGameTimeManager::GetInstance();
    if (TimeManager)
    {
        if (!TimeManager->OnTimeChanged.IsAlreadyBound(this, &UBTTask_Stay::OnTimeChanged))
        {
            TimeManager->OnTimeChanged.AddDynamic(this, &UBTTask_Stay::OnTimeChanged);
        }
    }

    BehaviorTreeCmp = &OwnerComp;

    return EBTNodeResult::InProgress;
}

void UBTTask_Stay::OnTimeChanged()
{
    FinishLatentTask(*BehaviorTreeCmp, EBTNodeResult::Succeeded);
}
