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
            UE_LOG(LogTemp, Log, TEXT("NPC %s is bound to OnTimeChanged event!"), *(OwnerComp.GetAIOwner()->GetPawn()->GetName()));
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("NPC %s is already bound to OnTimeChanged event!"), *(OwnerComp.GetAIOwner()->GetPawn()->GetName()));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: TimeManager is nullptr in ExecuteTask!"));
    }

    BehaviorTreeCmp = &OwnerComp;

    UE_LOG(LogTemp, Log, TEXT("NPC %s entered Stay state"), *(OwnerComp.GetAIOwner()->GetPawn()->GetName()));

    return EBTNodeResult::InProgress;
}

void UBTTask_Stay::OnTimeChanged()
{
    if (!BehaviorTreeCmp)
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: BehaviorTreeCmp is nullptr in OnTimeChanged!"));
        return;
    }

    if (!BehaviorTreeCmp->GetAIOwner())
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: AI Owner is nullptr in OnTimeChanged!"));
        return;
    }

    APawn* ControlledPawn = BehaviorTreeCmp->GetAIOwner()->GetPawn();
    if (!ControlledPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: ControlledPawn is nullptr in OnTimeChanged!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Exit Stay State: %s"), *ControlledPawn->GetName());

    FinishLatentTask(*BehaviorTreeCmp, EBTNodeResult::Succeeded);
}
