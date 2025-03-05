// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TeamManager.h"

UTeamManager* UTeamManager::Instance = nullptr;  // 정적 변수 초기화

void UTeamManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    // 현재 활성화된 월드 찾기
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
    // 이미 캐싱된 인스턴스가 있다면 즉시 반환
    if (Instance)
    {
        return Instance;
    }

    // 캐싱된 값이 없다면, 다시 찾고 캐싱
    if (GEngine)
    {
        // 현재 활성화된 월드 찾기
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
    // 대칭 관계 설정
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

