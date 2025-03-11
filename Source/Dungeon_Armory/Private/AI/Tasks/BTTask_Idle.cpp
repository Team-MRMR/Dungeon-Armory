// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Idle.h"
#include "Characters/NPC/NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Idle::UBTTask_Idle()
{
    bNotifyTick = true;

    NodeName = "Idle"; // ��� �̸� ����
    ElapsedTime = 0.0f;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ElapsedTime = 0.0f;
	IdleDuration = FMath::FRandRange(1.0f, 5.0f); // ��� �ð� ����
	UE_LOG(LogTemp, Warning, TEXT("Idle Duration: %f"), IdleDuration);
    return EBTNodeResult::InProgress; // ��� ����
}

void UBTTask_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    ElapsedTime += DeltaSeconds;
    if (ElapsedTime >= IdleDuration)
    {
		Cast<ANPCAIController>(OwnerComp.GetAIOwner())->SetNPCState(ENPCStates::Patrol); // ���� ����
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    UE_LOG(LogTemp, Warning, TEXT("Elapsed Time: %f / Idle Duration: %f"), ElapsedTime, IdleDuration);
}