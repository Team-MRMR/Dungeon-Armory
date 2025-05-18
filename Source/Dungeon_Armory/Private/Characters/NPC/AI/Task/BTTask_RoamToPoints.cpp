// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/NPC/AI/Task/BTTask_RoamToPoints.h"
#include "Characters/NPC/NPCBase.h"

#include "Characters/Core/AI/AIControllerBase.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RoamToPoints::UBTTask_RoamToPoints()
{
    NodeName = "RoamToPoints"; // BT���� ���̴� �̸�
}

EBTNodeResult::Type UBTTask_RoamToPoints::ExecuteTask(UBehaviorTreeComponent& OwnerCmp, uint8* NodeMemory)
{
    auto NPCController = Cast<AAIControllerBase>(OwnerCmp.GetAIOwner());
    if (!NPCController)
    {
        return EBTNodeResult::Failed;
    }

	auto* NPC = Cast<ANPCBase>(NPCController->GetPawn());
	if (!NPC)
	{
		return EBTNodeResult::Failed;
	}

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSystem)
    {
        return EBTNodeResult::Failed;
    }

    // �̵� ��� ����
    FVector MovePointLocation = NPC->GetNextPoint();
    NPCController->MoveToLocation(MovePointLocation);

    // �̵� �Ϸ� �� OnRoamToPointReached���� ó��, OnRoamingReached ȣ��

    return EBTNodeResult::InProgress;
}

void UBTTask_RoamToPoints::OnRoamingReached(UBehaviorTreeComponent* BehaviorTreeComp)
{
    FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Succeeded);
}
