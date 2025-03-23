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

    // 게임 시간 매니저 찾기
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

    // 비헤이비어 트리 실행
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // 블랙보드 설정 (AIController에서 관리됨)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // 블랙보드 변수 초기화
        if (BlackboardComponent)
        {
            BlackboardComponent->SetValueAsVector("HomeLocation", GetPawn()->GetActorLocation());
            SetNPCState(ENPCStates::Stay);

            // 비헤이비어 트리 실행 (이 시점에서 BehaviorTreeComponent가 자동으로 생성됨)
            RunBehaviorTree(BehaviorTree);

            // 내부적으로 생성된 BehaviorTreeComponent를 가져와서 멤버 변수에 할당
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
