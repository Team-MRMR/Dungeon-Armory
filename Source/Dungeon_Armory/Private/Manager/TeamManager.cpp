// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TeamManager.h"

void UTeamManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitializeTeamRelationMap();
}

UTeamManager* UTeamManager::GetInstance(UObject* WorldContextObject)
{
    if (WorldContextObject)
    {
        if (UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance())
        {
            return GameInstance->GetSubsystem<UTeamManager>();
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

