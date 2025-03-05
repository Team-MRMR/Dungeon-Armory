// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TeamManager.h"

UTeamManager* UTeamManager::Instance = nullptr;  // ���� ���� �ʱ�ȭ

void UTeamManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    // ���� Ȱ��ȭ�� ���� ã��
    for (const FWorldContext& Context : GEngine->GetWorldContexts())
    {
        if (Context.World())
        {
            if (UGameInstance* GameInstance = Context.World()->GetGameInstance())
            {
                Instance = GameInstance->GetSubsystem<UTeamManager>();
            }
        }
    }

	InitializeTeamRelationMap();
}

UTeamManager* UTeamManager::GetInstance()
{
    // �̹� ĳ�̵� �ν��Ͻ��� �ִٸ� ��� ��ȯ
    if (Instance)
    {
        return Instance;
    }

    // ĳ�̵� ���� ���ٸ�, �ٽ� ã�� ĳ��
    if (GEngine)
    {
        // ���� Ȱ��ȭ�� ���� ã��
        for (const FWorldContext& Context : GEngine->GetWorldContexts())
        {
            if (Context.World())
            {
                if (UGameInstance* GameInstance = Context.World()->GetGameInstance())
                {
                    Instance = GameInstance->GetSubsystem<UTeamManager>();
                    return Instance;
                }
            }
        }
    }

    return nullptr;
}

TMap<ETeamType, ERelationType> UTeamManager::GetTeamRelation(ETeamType OneTeam) const
{
    return TeamRelationMap.FindRef(OneTeam).RelationMap;
}

void UTeamManager::SetTeamRelation(ETeamType TeamA, ETeamType TeamB, ERelationType Releation)
{
    // ��Ī ���� ����
	TeamRelationMap.FindOrAdd(TeamA).RelationMap.FindOrAdd(TeamB) = Releation;
	TeamRelationMap.FindOrAdd(TeamB).RelationMap.FindOrAdd(TeamA) = Releation;
}

ERelationType UTeamManager::GetRelation(ETeamType TeamA, ETeamType TeamB) const
{
    if (const auto TeamRelation = TeamRelationMap.Find(TeamA))
    {
        if (const auto Relation = TeamRelation->RelationMap.Find(TeamB))
        {
			return *Relation;
        }

        return ERelationType::None;
    }

    return ERelationType::None;
}

void UTeamManager::InitializeTeamRelationMap()
{
	TeamRelationMap.Empty();
}

