// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Stay.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/NPC/NPCAIController.h"
#include "Manager/InGameTimeManager.h"

UBTTask_Stay::UBTTask_Stay()
{
	NodeName = "Stay";
}

EBTNodeResult::Type UBTTask_Stay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

// ��Ʈ�ѷ��� OnExitStay �Լ����� ��ȣ��
void UBTTask_Stay::WakeRoutine(UBehaviorTreeComponent* BehaviorTreeComponent)
{
    FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}
