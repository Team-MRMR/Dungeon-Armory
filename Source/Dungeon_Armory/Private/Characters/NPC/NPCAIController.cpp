// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCAIController.h"
#include "Characters/NPC/NPCBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Manager/TeamManager.h"

//#include "Perception/AIPerceptionStimuliSourceComponent.h"

ANPCAIController::ANPCAIController()
{
    // 비헤이비어 트리와 블랙보드 컴포넌트 생성
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

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

void ANPCAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAIState();
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ANPCBase* NPC = Cast<ANPCBase>(InPawn))
    {
        // 컨트롤러가 소유한 NPC 가져오기
        BehaviorTree = NPC->BehaviorTree;
        if (BehaviorTree)
        {
            UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
            RunBehaviorTree(BehaviorTree);

            // 초기 블랙보드 값 설정
            BlackboardComponent->SetValueAsVector("HomeLocation", NPC->GetActorLocation());
            SetNPCState(ENPCStates::Patrol);
        }

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
    if (!BlackboardComponent)
    {
        return;
    }

    bDetectedTarget = Stimulus.WasSuccessfullySensed();
    if (bDetectedTarget)
    {
        SetNPCState(ENPCStates::Chase);
        BlackboardComponent->SetValueAsObject("Target", Actor);
    }
    else
    {
        BlackboardComponent->SetValueAsObject("Target", nullptr);

    }

    UE_LOG(LogTemp, Warning, TEXT("AI Perception: %s detected!"), bDetectedTarget ? TEXT("Target") : TEXT("None"));
}

void ANPCAIController::UpdateAIState()
{
    if (!BlackboardComponent)
    {
        return;
    }

    if (bDetectedTarget)
    {
        if (GetNPCState() != ENPCStates::Chase)
        {
            SetNPCState(ENPCStates::Chase);
            return;
        }
    }

    ENPCStates CurrState = GetNPCState();
    switch (CurrState)
    {
    case ENPCStates::Chase:
        // 적을 감지하지 못했으면 Return으로 변경
        SetNPCState(ENPCStates::Return);
        break;
    case ENPCStates::Return:
		SetNPCState(ENPCStates::Patrol);
        //// 목표 지점에 도착했으면 Idle 상태로 변경
        //if (HasReachedHomePosition())
        //{
        //    SetNPCState(ENPCStates::Idle);
        //}
        break;
    default:
        break;
    }
}

void ANPCAIController::SetNPCState(ENPCStates NewNPCState)
{
    if (!BlackboardComponent)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum(NPCState, static_cast<uint8>(NewNPCState));
}

ENPCStates ANPCAIController::GetNPCState() const
{
    if (!BlackboardComponent)
    {
        return ENPCStates::None;
    }

    int8 CurrNPCState = BlackboardComponent->GetValueAsEnum(NPCState);
	return static_cast<ENPCStates>(CurrNPCState);
}
