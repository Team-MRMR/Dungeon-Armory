// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Stay.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/NPC/NPCAIControllerBase.h"
#include "Manager/InGameTimeManager.h"

UBTTask_Stay::UBTTask_Stay()
{
	NodeName = "Stay";
}

EBTNodeResult::Type UBTTask_Stay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

// 컨트롤러의 OnStayCompleted 함수에서 호출
void UBTTask_Stay::OnStayingCompleted(UBehaviorTreeComponent* BehaviorTreeComponent)
{
    FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}
