// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"

#include "AI/Tasks/BTTask_Stay.h"
#include "AI/Tasks/BTTask_MoveToPoint.h"
#include "AI/Tasks/BTTask_RoamToPoints.h"

#include "Manager/InGameTimeManager.h"

ANPCAIController::ANPCAIController()
{

}

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // 비헤이비어 트리 실행
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // 블랙보드 설정 (AIController에서 관리됨)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // 블랙보드 변수 초기화
        if (BlackboardComponent)
        {
            BlackboardComponent->SetValueAsFloat("MovementSpeed", 500.0f);

            BlackboardComponent->SetValueAsVector("HomeLocation", GetPawn()->GetActorLocation());
            SetNPCState(ENPCStates::Stay);

            // 비헤이비어 트리 실행 (이 시점에서 BehaviorTreeComponent가 자동으로 생성됨)
            RunBehaviorTree(BehaviorTree);

            // 내부적으로 생성된 BehaviorTreeComponent를 가져와서 멤버 변수에 할당
            BehaviorTreeComponent = FindComponentByClass<UBehaviorTreeComponent>();
        }
    }
}


ENPCStates ANPCAIController::GetNPCState() const
{
    if (BlackboardComponent == nullptr)
    {
        return ENPCStates::None;
    }

    int8 CurrNPCState = BlackboardComponent->GetValueAsEnum(BBKey_NPCState);
    return static_cast<ENPCStates>(CurrNPCState);
}

void ANPCAIController::SetNPCState(ENPCStates NewNPCState)
{
    if (BlackboardComponent == nullptr)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum(BBKey_NPCState, static_cast<uint8>(NewNPCState));
}


void ANPCAIController::OnStayCompleted()
{
    if (GetNPCState() != ENPCStates::Stay)
    {
        return;
    }

    if (!BehaviorTreeComponent)
    {
        return;
    }

    const UBTNode* ActiveNode = BehaviorTreeComponent->GetActiveNode();
    if (ActiveNode)
    {
        UBTTask_Stay* StayTask = const_cast<UBTTask_Stay*>(Cast<UBTTask_Stay>(ActiveNode));
        if (StayTask)
        {
            StayTask->OnStayingCompleted(BehaviorTreeComponent);
            SetNPCState(ENPCStates::RoamToPoints);
        }
    }
}

void ANPCAIController::OnMoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    if (GetNPCState() != ENPCStates::MoveToPoint)
    {
        return;
    }

    if (!BehaviorTreeComponent)
    {
        return;
    }

    const UBTNode* ActiveNode = BehaviorTreeComponent->GetActiveNode();
    if (ActiveNode)
    {
        UBTTask_MoveToPoint* MoveToPointTask = const_cast<UBTTask_MoveToPoint*>(Cast<UBTTask_MoveToPoint>(ActiveNode));
        if (MoveToPointTask)
        {
            MoveToPointTask->OnMovingCompleted(BehaviorTreeComponent);
            SetNPCState(ENPCStates::Stay);
        }
    }
}

void ANPCAIController::OnRoamToPointReached(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    if (GetNPCState() != ENPCStates::RoamToPoints)
    {
        return;
    }

    if (!BehaviorTreeComponent)
    {
        return;
    }

    const UBTNode* ActiveNode = BehaviorTreeComponent->GetActiveNode();
    if (ActiveNode)
    {
        UBTTask_RoamToPoints* RoamToPointsTask = const_cast<UBTTask_RoamToPoints*>(Cast<UBTTask_RoamToPoints>(ActiveNode));
        if (RoamToPointsTask)
        {
            RoamToPointsTask->OnRoamingReached(BehaviorTreeComponent);
            SetNPCState(ENPCStates::Wait);
        }
    }
}
