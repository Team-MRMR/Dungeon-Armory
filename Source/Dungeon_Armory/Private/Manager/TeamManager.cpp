// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TeamManager.h"

void UTeamManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

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
    // 대칭 관계 유지
	TeamRelationMap.FindOrAdd(TeamA).RelationMap.FindOrAdd(TeamB) = Releation;
	TeamRelationMap.FindOrAdd(TeamB).RelationMap.FindOrAdd(TeamA) = Releation;
}

void UTeamManager::InitializeTeamRelation()
{
}

