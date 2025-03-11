// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Idle.h"
#include "Characters/NPC/NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Idle::UBTTask_Idle()
{
    bNotifyTick = true;

    NodeName = "Idle"; // 노드 이름 설정
    ElapsedTime = 0.0f;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ElapsedTime = 0.0f;
	IdleDuration = FMath::FRandRange(1.0f, 5.0f); // 대기 시간 설정
	UE_LOG(LogTemp, Warning, TEXT("Idle Duration: %f"), IdleDuration);
    return EBTNodeResult::InProgress; // 대기 시작
}

void UBTTask_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    ElapsedTime += DeltaSeconds;
    if (ElapsedTime >= IdleDuration)
    {
		Cast<ANPCAIController>(OwnerComp.GetAIOwner())->SetNPCState(ENPCStates::Patrol); // 상태 변경
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    UE_LOG(LogTemp, Warning, TEXT("Elapsed Time: %f / Idle Duration: %f"), ElapsedTime, IdleDuration);
}