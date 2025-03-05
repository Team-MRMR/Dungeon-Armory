// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyAIController.h"
#include "Characters/Enemy/EnemyBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

//#include "Perception/AIPerceptionStimuliSourceComponent.h"

AEnemyAIController::AEnemyAIController()
{
    // �����̺�� Ʈ���� ������ ������Ʈ ����
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // AI ���� �ý��� �ʱ�ȭ
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // ���� ���� ����
    SightConfig->SightRadius = 2000.0f; // AI�� ������ �ִ� �Ÿ�
    SightConfig->LoseSightRadius = 2500.0f; // ���� �� �Ҿ������ �Ÿ�
    SightConfig->PeripheralVisionAngleDegrees = 120.0f; // �þ߰� 120��
    SightConfig->SetMaxAge(5.0f); // ���� ���� ���� �ð�

    // ���� ���� ����
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

            // �ʱ� ������ �� ����
            BlackboardComponent->SetValueAsVector("HomeLocation", Enemy->GetActorLocation());
            SetEnemyState(EEnemyStates::Patrol);
        }
    }

    if (IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(InPawn))
    {
		SetGenericTeamId(TeamAgent->GetGenericTeamId());
    }
}

// ���� �̺�Ʈ ó��
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
        // ���� �������� �������� Return���� ����
        SetEnemyState(EEnemyStates::Return);
        break;
    case EEnemyStates::Return:
		SetEnemyState(EEnemyStates::Patrol);
        //// ��ǥ ������ ���������� Idle ���·� ����
        //if (HasReachedHomePosition())
        //{
        //    SetEnemyState(EEnemyStates::Idle);
        //}
        break;
    default:
        break;
    }
}