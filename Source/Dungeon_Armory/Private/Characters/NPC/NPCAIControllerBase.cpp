// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCAIControllerBase.h"
#include "Characters/NPC/NPCBase.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Manager/TeamManager.h"

#include "AI/Team/TeamComponent.h"

ANPCAIControllerBase::ANPCAIControllerBase()
{
    PrimaryActorTick.bCanEverTick = false;

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
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIControllerBase::OnTargetPerceived);

    // �� ���̵� �ʱ�ȭ
	TeamId = FGenericTeamId::NoTeam;
}

void ANPCAIControllerBase::BeginPlay()
{
    Super::BeginPlay();

}

void ANPCAIControllerBase::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ANPCBase* NPC = Cast<ANPCBase>(InPawn))
    {
        // TeamComponent���� �� ������ ������
        if (UTeamComponent* TeamCmp = NPC->TeamComponent)
        {
            TeamComponent = TeamCmp; // �� ������ ������ ����
        }
    }

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

void ANPCAIControllerBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

ETeamAttitude::Type ANPCAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
    if (TeamComponent)
    {
		return TeamComponent->GetTeamAttitudeTowards(Other);
    }

	return ETeamAttitude::Neutral;
}

FGenericTeamId ANPCAIControllerBase::GetGenericTeamId() const
{
    if (TeamComponent)
    {
        return TeamComponent->GetGenericTeamId();
    }

    return FGenericTeamId::NoTeam;
}

// ���� �̺�Ʈ ó��
void ANPCAIControllerBase::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
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

ENPCStates ANPCAIControllerBase::GetNPCState() const
{
    if (BlackboardComponent == nullptr)
    {
        return ENPCStates::None;
    }

    int8 CurrNPCState = BlackboardComponent->GetValueAsEnum(BBKey_NPCState);
    return static_cast<ENPCStates>(CurrNPCState);
}

void ANPCAIControllerBase::SetNPCState(ENPCStates NewNPCState)
{
    if (BlackboardComponent == nullptr)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum(BBKey_NPCState, static_cast<uint8>(NewNPCState));
}
