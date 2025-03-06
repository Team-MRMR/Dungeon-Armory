// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Idle.h"
#include "Characters/NPC/NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Idle::UBTTask_Idle()
{
    NodeName = "Idle"; // 노드 이름 설정
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //UE_LOG(LogTemp, Log, TEXT("AI Idle 상태"));

    // 일정 시간 대기 후 완료
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindLambda([&]()
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    });

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        AIController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.5f, false);
        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}