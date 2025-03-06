// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Idle.h"
#include "Characters/NPC/NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Idle::UBTTask_Idle()
{
    NodeName = "Idle"; // ��� �̸� ����
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //UE_LOG(LogTemp, Log, TEXT("AI Idle ����"));

    // ���� �ð� ��� �� �Ϸ�
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