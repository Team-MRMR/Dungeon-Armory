// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/BTTask_RoamToPoints.h"
#include "AIController.h"
#include "AITypes.h"                            // FAIRequestID, EPathFollowingRequestResult
#include "Navigation/PathFollowingComponent.h"  // EPathFollowingResult
#include "NavigationSystem.h"
#include "Characters/NPC/DynamicNPCAIController.h"
#include "Characters/NPC/NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RoamToPoints::UBTTask_RoamToPoints()
{
    NodeName = "RoamToPoints"; // BT���� ���̴� �̸�
}

EBTNodeResult::Type UBTTask_RoamToPoints::ExecuteTask(UBehaviorTreeComponent& OwnerCmp, uint8* NodeMemory)
{
    auto NPCController = Cast<ANPCAIController>(OwnerCmp.GetAIOwner());
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
    FVector MovePointLocation = NPC->GetNextMovePoint();
    NPCController->MoveToLocation(MovePointLocation);

    // �̵� �Ϸ� �� OnRoamToPointReached���� ó��, OnRoamingReached ȣ��

    return EBTNodeResult::InProgress;
}

void UBTTask_RoamToPoints::OnRoamingReached(UBehaviorTreeComponent* BehaviorTreeComp)
{
    FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Succeeded);
}
