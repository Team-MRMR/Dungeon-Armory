// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/AIControllerBase.h"
#include "Characters/NPC/NPCBase.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Manager/TeamManager.h"

#include "AI/Team/TeamComponent.h"

AAIControllerBase::AAIControllerBase()
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
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerBase::OnTargetPerceived);

    // �� ���̵� �ʱ�ȭ
	TeamId = FGenericTeamId::NoTeam;
}

void AAIControllerBase::BeginPlay()
{
    Super::BeginPlay();

}

void AAIControllerBase::OnPossess(APawn* InPawn)
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
}

void AAIControllerBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

ETeamAttitude::Type AAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
    if (TeamComponent)
    {
		return TeamComponent->GetTeamAttitudeTowards(Other);
    }

	return ETeamAttitude::Neutral;
}

FGenericTeamId AAIControllerBase::GetGenericTeamId() const
{
    if (TeamComponent)
    {
        return TeamComponent->GetGenericTeamId();
    }

    return FGenericTeamId::NoTeam;
}

// ���� �̺�Ʈ ó��
void AAIControllerBase::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
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


