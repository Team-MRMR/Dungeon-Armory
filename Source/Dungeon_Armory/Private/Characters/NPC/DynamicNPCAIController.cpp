// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/DynamicNPCAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"

#include "AI/Tasks/BTTask_Stay.h"
#include "AI/Tasks/BTTask_MoveToPoint.h"
#include "AI/Tasks/BTTask_RoamToPoints.h"

#include "Manager/InGameTimeManager.h"

/***** Base Class *****/

void ADynamicNPCAIController::BeginPlay()
{
    Super::BeginPlay();

    // ���� �ð� �Ŵ��� ã��
    UInGameTimeManager* TimeManager = UInGameTimeManager::GetInstance();
    if (TimeManager)
    {
        TimeManager->OnTimePeriodChanged.AddDynamic(this, &ADynamicNPCAIController::OnStayCompleted);
    }

    ReceiveMoveCompleted.AddDynamic(this, &ADynamicNPCAIController::OnRoamToPointReached);

}

void ADynamicNPCAIController::OnPossess(APawn* InPawn)
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

/***** Derived Class *****/

void ADynamicNPCAIController::OnStayCompleted()
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

void ADynamicNPCAIController::OnRoamToPointReached(FAIRequestID RequestID, EPathFollowingResult::Type Result)
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
			//SetNPCState(ENPCStates::Wait);
        }
    }
}
