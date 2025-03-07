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
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetPerceived);

    // �� ���̵� �ʱ�ȭ
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
        // ��Ʈ�ѷ��� ������ NPC ��������
        BehaviorTree = NPC->BehaviorTree;
        if (BehaviorTree)
        {
            UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
            RunBehaviorTree(BehaviorTree);

            // �ʱ� ������ �� ����
            BlackboardComponent->SetValueAsVector("HomeLocation", NPC->GetActorLocation());
            SetNPCState(ENPCStates::Patrol);
        }

        // TeamComponent���� �� ������ ������
        if (UTeamComponent* TeamCmp = NPC->TeamComponent)
        {
            TeamComponent = TeamCmp; // �� ������ ������ ����
        }
    }
}

// ���� �̺�Ʈ ó��
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
        // ���� �������� �������� Return���� ����
        SetNPCState(ENPCStates::Return);
        break;
    case ENPCStates::Return:
		SetNPCState(ENPCStates::Patrol);
        //// ��ǥ ������ ���������� Idle ���·� ����
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
