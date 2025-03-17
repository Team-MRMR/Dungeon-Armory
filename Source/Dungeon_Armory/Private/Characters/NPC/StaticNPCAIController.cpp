// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/StaticNPCAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Manager/InGameTimeManager.h"

/***** Base Class *****/

void AStaticNPCAIController::BeginPlay()
{
	Super::BeginPlay();

    // 게임 시간 매니저 찾기
    UInGameTimeManager* TimeManager = UInGameTimeManager::GetInstance();
    if (TimeManager)
    {
        TimeManager->OnTimeChanged.AddDynamic(this, &AStaticNPCAIController::OnTimeChanged);
    }
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
        }
    }
}

/***** Derived Class *****/

void AStaticNPCAIController::OnTimeChanged()
{
    SetNPCState(ENPCStates::MoveToPoint);
}
