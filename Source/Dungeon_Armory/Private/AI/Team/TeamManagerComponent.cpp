// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Team/TeamManagerComponent.h"

// Sets default values for this component's properties
UTeamManagerComponent::UTeamManagerComponent()
{
	InitializeTeamRelation();
}

ERelationType UTeamManagerComponent::GetTeamRelationMap(ETeamType TeamA, ETeamType TeamB) const
{
	if (const auto InnerStruct = TeamRelationMap.Find(TeamA))
	{
		if (const ERelationType* Relation = InnerStruct->RelationMap.Find(TeamB))
		{
			return *Relation;
		}

		return ERelationType::None;
	}

	return ERelationType::None;
}

void UTeamManagerComponent::SetTeamRelationMap(ETeamType TeamA, ETeamType TeamB, ERelationType Releation)
{
	TeamRelationMap.FindOrAdd(TeamA).RelationMap.FindOrAdd(TeamB) = Releation;
	TeamRelationMap.FindOrAdd(TeamB).RelationMap.FindOrAdd(TeamA) = Releation;
}

void UTeamManagerComponent::InitializeTeamRelation()
{
	SetTeamRelationMap(ETeamType::Player, ETeamType::NPC, ERelationType::Neutral);
	SetTeamRelationMap(ETeamType::Player, ETeamType::Mob, ERelationType::Hostile);

	SetTeamRelationMap(ETeamType::NPC, ETeamType::Mob, ERelationType::Hostile);
}
