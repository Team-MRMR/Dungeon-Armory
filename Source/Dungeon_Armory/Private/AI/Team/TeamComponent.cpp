// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Team/TeamComponent.h"
#include "Manager/TeamManager.h"

// Sets default values for this component's properties
UTeamComponent::UTeamComponent()
{
	TeamType = ETeamType::None;
	TeamId = FGenericTeamId::NoTeam;
}

ETeamType UTeamComponent::GetTeamType() const
{
	return static_cast<ETeamType>(TeamId.GetId());
}

void UTeamComponent::SetTeamType(const ETeamType NewTeamType)
{
	SetGenericTeamId(FGenericTeamId(static_cast<uint8>(NewTeamType)));
}

ETeamAttitude::Type UTeamComponent::GetTeamAttitudeTowards(const AActor& Other) const
{
    ETeamType OwnTeamType = GetTeamType();
    ETeamType OtherTeamType = Other.GetComponentByClass<UTeamComponent>()->GetTeamType();

    switch (UTeamManager::GetInstance()->GetRelation(OwnTeamType, OtherTeamType))
    {
    case ERelationType::Friendly:
        return ETeamAttitude::Friendly;
    case ERelationType::Hostile:
        return ETeamAttitude::Hostile;
    case ERelationType::Neutral:
        return ETeamAttitude::Neutral;
    }

	return ETeamAttitude::Neutral;
}

FGenericTeamId UTeamComponent::GetGenericTeamId() const
{
	return TeamId;
}

void UTeamComponent::SetGenericTeamId(const FGenericTeamId& NewTeamId)
{
	TeamId = NewTeamId;
}

void UTeamComponent::BeginPlay()
{
	Super::BeginPlay();

	SetGenericTeamId(FGenericTeamId(static_cast<uint8>(TeamType)));
}
