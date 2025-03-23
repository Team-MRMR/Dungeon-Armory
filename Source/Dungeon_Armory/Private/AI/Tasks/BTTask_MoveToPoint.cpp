// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_MoveToPoint.h"
#include "AIController.h"
#include "AITypes.h"                            // FAIRequestID, EPathFollowingRequestResult
#include "Navigation/PathFollowingComponent.h"  // EPathFollowingResult
#include "NavigationSystem.h"
#include "Characters/NPC/DynamicNPCAIController.h"
#include "Characters/NPC/NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/NPC/MovePoint.h"


UBTTask_MoveToPoint::UBTTask_MoveToPoint()
{
    NodeName = "MoveToPoint"; // BT���� ���̴� �̸�
}

EBTNodeResult::Type UBTTask_MoveToPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto NPCController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
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
    FVector StayPointLocation = NPC->GetStayPoint();
    NPCController->MoveToLocation(StayPointLocation);

    // �̵� �Ϸ� �� OnMoveToPointCompleted���� ó��, OnMovingCompleted ȣ��

    return EBTNodeResult::InProgress;
}

void UBTTask_MoveToPoint::OnMovingCompleted(UBehaviorTreeComponent* BehaviorTreeComp)
{
    
	UE_LOG(LogTemp, Log, TEXT("%10s OnMovingCompleted"), *BehaviorTreeComp->GetAIOwner()->GetName());
    FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Succeeded);
}
