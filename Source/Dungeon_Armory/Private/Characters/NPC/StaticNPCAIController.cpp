// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/StaticNPCAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"

#include "AI/Tasks/BTTask_Stay.h"
#include "AI/Tasks/BTTask_MoveToPoint.h"
#include "AI/Tasks/BTTask_RoamToPoints.h"

#include "Manager/InGameTimeManager.h"

/***** Base Class *****/

AStaticNPCAIController::AStaticNPCAIController()
{

}

void AStaticNPCAIController::BeginPlay()
{
	Super::BeginPlay();

    // ���� �ð� �Ŵ��� ã��
    UInGameTimeManager* TimeManager = UInGameTimeManager::GetInstance();
    if (TimeManager)
    {
        TimeManager->OnTimePeriodChanged.AddDynamic(this, &AStaticNPCAIController::OnStayCompleted);
    }

    ReceiveMoveCompleted.AddDynamic(this, &AStaticNPCAIController::OnMoveToPointCompleted);

}

void AStaticNPCAIController::OnPossess(APawn* InPawn)
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

void AStaticNPCAIController::OnStayCompleted()
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
            SetNPCState(ENPCStates::MoveToPoint);
        }
    }
}

void AStaticNPCAIController::OnMoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
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
