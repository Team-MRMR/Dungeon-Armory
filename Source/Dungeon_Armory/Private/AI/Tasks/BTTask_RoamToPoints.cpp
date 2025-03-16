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
    NodeName = "RoamToPoints"; // BT에서 보이는 이름
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

	BehaviorTreeCmp = &OwnerCmp;

    // 이동 명령 실행
    FVector MovePointLocation = NPC->GetNextMovePoint();

    NPCController->MoveToLocation(MovePointLocation);
    if (!NPCController->ReceiveMoveCompleted.IsAlreadyBound(this, &UBTTask_RoamToPoints::OnMoveCompleted))
    {
        NPCController->ReceiveMoveCompleted.AddDynamic(this, &UBTTask_RoamToPoints::OnMoveCompleted);
    }

    return EBTNodeResult::InProgress; // 이동 완료 후 OnMoveCompleted에서 처리
}

void UBTTask_RoamToPoints::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    ANPCAIController* NPCController = Cast<ANPCAIController>(BehaviorTreeCmp->GetAIOwner());
    if (NPCController)
    {
        NPCController->SetNPCState(ENPCStates::Wait); // Wait 상태로 변경
    }

    FinishLatentTask(*BehaviorTreeCmp, EBTNodeResult::Succeeded);
}
