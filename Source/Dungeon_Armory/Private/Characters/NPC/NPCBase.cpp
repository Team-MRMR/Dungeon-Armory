// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCBase.h"
#include "Characters/NPC/NPCAIController.h"
#include "Characters/NPC/NPCPatrolPoint.h"

// Sets default values
ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ÆÀ ÄÄÆ÷³ÍÆ® »ý¼º
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));

}

FGenericTeamId ANPCBase::GetGenericTeamId() const
{
	return TeamComponent->GetGenericTeamId();
}

void ANPCBase::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamComponent->SetTeamType(static_cast<ETeamType>(NewTeamID.GetId()));
}

FVector ANPCBase::GetNextPatrolPoint()
{
	if (PatrolPoints.Num() == 0)
	{
		return GetActorLocation();
	}

	FVector NextPoint = PatrolPoints[CurrentPatrolIndex]->GetPatrolLocation();
	CurrentPatrolIndex = (CurrentPatrolIndex + 1) % PatrolPoints.Num();
	return NextPoint;
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

