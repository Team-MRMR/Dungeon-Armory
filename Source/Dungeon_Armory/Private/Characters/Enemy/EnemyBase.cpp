// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyBase.h"



// Sets default values
AEnemyBase::AEnemyBase()
{
	// Create Team Component and 
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
    
}

FGenericTeamId AEnemyBase::GetGenericTeamId() const
{
	return FGenericTeamId(static_cast<uint8>(TeamComponent->GetTeamType()));
}

void AEnemyBase::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamComponent->SetTeamType(static_cast<ETeamType>(NewTeamID.GetId()));
}

ETeamAttitude::Type AEnemyBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	ETeamType OwnTeamType = TeamComponent->GetTeamType();
	ETeamType OtherTeamType = Other.GetComponentByClass<UTeamComponent>()->GetTeamType();

	switch (UTeamManager::GetInstance()->GetRelation(OwnTeamType, OtherTeamType))
	{
	case ERelationType::Friendly:
		return ETeamAttitude::Friendly;
	case ERelationType::Hostile:
		return ETeamAttitude::Hostile;
	case ERelationType::Neutral:
	default:
		return ETeamAttitude::Neutral;
	}
}

ETeamAttitude::Type AEnemyBase::CustomAttitudeSolver(FGenericTeamId TeamA, FGenericTeamId TeamB)
{
	ETeamType OwnTeamType = static_cast<ETeamType>(TeamA.GetId());
	ETeamType OtherTeamType = static_cast<ETeamType>(TeamB.GetId());

	switch (UTeamManager::GetInstance()->GetRelation(OwnTeamType, OtherTeamType))
	{
	case ERelationType::Friendly:
		return ETeamAttitude::Friendly;
	case ERelationType::Hostile:
		return ETeamAttitude::Hostile;
	case ERelationType::Neutral:
	default:
		return ETeamAttitude::Neutral;
	}
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	//FGenericTeamId::SetAttitudeSolver(CustomAttitudeSolver);
}

