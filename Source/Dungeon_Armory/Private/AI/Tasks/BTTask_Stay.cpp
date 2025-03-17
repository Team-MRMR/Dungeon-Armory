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
    // 게임 시간 매니저 찾기
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
