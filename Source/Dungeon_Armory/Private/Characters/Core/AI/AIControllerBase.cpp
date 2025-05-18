// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/AI/AIControllerBase.h"
#include "Characters/NPC/NPCBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Manager/TeamManager.h"

#include "Characters/Core/AI/Team/TeamComponent.h"

AAIControllerBase::AAIControllerBase()
{
    PrimaryActorTick.bCanEverTick = false;

    // AI ���� �ý��� �ʱ�ȭ
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // �� ������Ʈ ����
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));

	// �����̺�� Ʈ�� ������Ʈ �ʱ�ȭ
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
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