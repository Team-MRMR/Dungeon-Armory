// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCAIController.h"
#include "Characters/NPC/NPCBase.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Manager/TeamManager.h"

ANPCAIController::ANPCAIController()
{
    // AI 감지 시스템 초기화
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // 감지 범위 설정
    SightConfig->SightRadius = 2000.0f; // AI가 감지할 최대 거리
    SightConfig->LoseSightRadius = 2500.0f; // 감지 후 잃어버리는 거리
    SightConfig->PeripheralVisionAngleDegrees = 120.0f; // 시야각 120도
    SightConfig->SetMaxAge(5.0f); // 감지 정보 유지 시간

    // 감지 설정 적용
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

    AIPerceptionComponent->ConfigureSense(*SightConfig);
    AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetPerceived);

    // 팀 아이디 초기화
	TeamId = FGenericTeamId::NoTeam;
}

ETeamAttitude::Type ANPCAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    if (TeamComponent)
    {
		return TeamComponent->GetTeamAttitudeTowards(Other);
    }

	return ETeamAttitude::Neutral;
}

FGenericTeamId ANPCAIController::GetGenericTeamId() const
{
    if (TeamComponent)
    {
        return TeamComponent->GetGenericTeamId();
    }

    return FGenericTeamId::NoTeam;
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

void ANPCAIController::BeginPlay()
{
    Super::BeginPlay();

    // 비헤이비어 트리 실행
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // 블랙보드 설정 (AIController에서 관리됨)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // 블랙보드 변수 초기화
        if (BlackboardComponent)
        {
            BlackboardComponent->SetValueAsVector("HomeLocation", GetOwner()->GetActorLocation());
            SetNPCState(ENPCStates::Idle);
        }

        // 비헤이비어 트리 실행 (이 시점에서 BehaviorTreeComponent가 자동으로 생성됨)
        RunBehaviorTree(BehaviorTree);
    }
}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ANPCBase* NPC = Cast<ANPCBase>(InPawn))
    {
        // TeamComponent에서 팀 정보를 가져옴
        if (UTeamComponent* TeamCmp = NPC->TeamComponent)
        {
            TeamComponent = TeamCmp; // 팀 정보를 가져와 저장
        }
    }
}

// 감지 이벤트 처리
void ANPCAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (BlackboardComponent == nullptr)
    {
        return;
    }
    bool bDetectedTarget = Stimulus.WasSuccessfullySensed();
    if (bDetectedTarget)
    {
        BlackboardComponent->SetValueAsObject("Target", Actor);
    }
    else
    {
        BlackboardComponent->SetValueAsObject("Target", nullptr);
    }
}
