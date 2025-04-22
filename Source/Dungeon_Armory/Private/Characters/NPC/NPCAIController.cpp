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

    // �����̺�� Ʈ�� ����
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // ������ ���� (AIController���� ������)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // ������ ���� �ʱ�ȭ
        if (BlackboardComponent)
        {
            BlackboardComponent->SetValueAsFloat("MovementSpeed", 500.0f);

            BlackboardComponent->SetValueAsVector("HomeLocation", GetPawn()->GetActorLocation());
            SetNPCState(ENPCStates::Stay);

            // �����̺�� Ʈ�� ���� (�� �������� BehaviorTreeComponent�� �ڵ����� ������)
            RunBehaviorTree(BehaviorTree);

            // ���������� ������ BehaviorTreeComponent�� �����ͼ� ��� ������ �Ҵ�
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
