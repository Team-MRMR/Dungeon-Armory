// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/AIController/MobAIController.h"

#include "AI/Interface/IMovableTask.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

AMobAIController::AMobAIController()
{
    PrimaryActorTick.bCanEverTick = false;

    SightConfig->SightRadius = 500.0f;
    SightConfig->LoseSightRadius = 700.f;
    SightConfig->PeripheralVisionAngleDegrees = 60.f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

    // Perception 컴포넌트에 시야 감지 설정 추가
    AIPerception->ConfigureSense(*SightConfig);

    // 우선순위가 가장 높은 감각으로 설정
    AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

    // 감지 이벤트 콜백 등록
    AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMobAIController::OnTargetPerceived);
}

void AMobAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AMobAIController::OnPossess(APawn* InPawn)
{
    // 팀 컴포넌트 설정
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
        }

        // 비헤이비어 트리 실행 (이 시점에서 BehaviorTreeComponent가 자동으로 생성됨)
        RunBehaviorTree(BehaviorTree);

        // 내부적으로 생성된 BehaviorTreeComponent를 가져와서 멤버 변수에 할당
        BehaviorTreeComponent = FindComponentByClass<UBehaviorTreeComponent>();
    }
}

void AMobAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    const UBTNode* ActiveNode = (BehaviorTreeComponent->GetActiveNode());
    if (ActiveNode)
	{
        // IIMovableTask 인터페이스를 사용하여 이동 완료 처리
        IIMovableTask* MovableTask = const_cast<IIMovableTask*>(Cast<IIMovableTask>(ActiveNode));
        if (MovableTask)
        {
            MovableTask->OnMoveCompleted(BehaviorTreeComponent);
        }
	}
}

// 감지 이벤트 처리
void AMobAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor)
        return;

    if (!BlackboardComponent)
        return;

    bool bDetectedTarget = Stimulus.WasSuccessfullySensed();
    if (bDetectedTarget)
    {
        // 플레이어가 감지됨
        DetectedPlayer = Actor;
        BlackboardComponent->SetValueAsObject("Target", Actor);
    }
    else
    {
        // 플레이어를 놓침
        if (DetectedPlayer == Actor)
        {
            DetectedPlayer = nullptr;
            BlackboardComponent->SetValueAsObject("Target", nullptr);
            // 상태를 Idle이나 Patrol로 변경하는 로직 추가
        }
    }
}
