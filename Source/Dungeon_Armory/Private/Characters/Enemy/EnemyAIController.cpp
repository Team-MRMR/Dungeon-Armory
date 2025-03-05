// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyAIController.h"
#include "Characters/Enemy/EnemyBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

//#include "Perception/AIPerceptionStimuliSourceComponent.h"

AEnemyAIController::AEnemyAIController()
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
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceived);
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAIState();
}

void AEnemyAIController::SetEnemyState(EEnemyStates NewEnemyState)
{
    if (!BlackboardComponent)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum(EnemyState, static_cast<uint8>(NewEnemyState));
}

EEnemyStates AEnemyAIController::GetEnemyState() const
{
    if (!BlackboardComponent)
    {
        return EEnemyStates::None;
    }

    int8 enemyState = BlackboardComponent->GetValueAsEnum(EnemyState);
	return static_cast<EEnemyStates>(enemyState);
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    /*ETeamType OwnTeamType = TeamComponent->GetTeamType();
    ETeamType OtherTeamType = Other.GetComponentByClass<UTeamComponent>()->GetTeamType();

    switch (UTeamManager::GetInstance()->GetRelation(OwnTeamType, OtherTeamType))
    {
    case ERelationType::Friendly:
        return ETeamAttitude::Friendly;
    case ERelationType::Hostile:
        return ETeamAttitude::Hostile;
    case ERelationType::Neutral:
    default:
        return ETeamAttitude::Neutral;
    }*/

    return ETeamAttitude::Friendly;
}

FGenericTeamId AEnemyAIController::GetGenericTeamId() const
{
    //return FGenericTeamId(static_cast<uint8>(TeamComponent->GetTeamType()));
	return FGenericTeamId(255);
}

void AEnemyAIController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
    //TeamComponent->SetTeamType(static_cast<ETeamType>(NewTeamID.GetId()));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (AEnemyBase* Enemy = Cast<AEnemyBase>(InPawn))
    {
        if (BehaviorTree)
        {
            UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
            RunBehaviorTree(BehaviorTree);

            // 초기 블랙보드 값 설정
            BlackboardComponent->SetValueAsVector("HomeLocation", Enemy->GetActorLocation());
            SetEnemyState(EEnemyStates::Patrol);
        }
    }

    if (IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(InPawn))
    {
		SetGenericTeamId(TeamAgent->GetGenericTeamId());
    }
}

// 감지 이벤트 처리
void AEnemyAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (!BlackboardComponent)
    {
        return;
    }

    bDetectedTarget = Stimulus.WasSuccessfullySensed();
    if (bDetectedTarget)
    {
        SetEnemyState(EEnemyStates::Chase);
        BlackboardComponent->SetValueAsObject("Target", Actor);
    }
    else
    {
        BlackboardComponent->SetValueAsObject("Target", nullptr);

    }

    UE_LOG(LogTemp, Warning, TEXT("AI Perception: %s detected!"), bDetectedTarget ? TEXT("Target") : TEXT("None"));
}

void AEnemyAIController::UpdateAIState()
{
    if (!BlackboardComponent)
    {
        return;
    }

    if (bDetectedTarget)
    {
        if (GetEnemyState() != EEnemyStates::Chase)
        {
            SetEnemyState(EEnemyStates::Chase);
            return;
        }
    }

    EEnemyStates CurrState = GetEnemyState();
    switch (CurrState)
    {
    case EEnemyStates::Chase:
        // 적을 감지하지 못했으면 Return으로 변경
        SetEnemyState(EEnemyStates::Return);
        break;
    case EEnemyStates::Return:
		SetEnemyState(EEnemyStates::Patrol);
        //// 목표 지점에 도착했으면 Idle 상태로 변경
        //if (HasReachedHomePosition())
        //{
        //    SetEnemyState(EEnemyStates::Idle);
        //}
        break;
    default:
        break;
    }
}