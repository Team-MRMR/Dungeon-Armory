// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCBase.h"
#include "Characters/NPC/NPCAIController.h"
#include "Characters/NPC/MovePoint.h"

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

FVector ANPCBase::GetNextMovePoint()
{
	if (MovePoints.Num() == 0)
	{
		return GetActorLocation();
	}

	FVector NextPoint = MovePoints[CurrMovepPointIndex]->GetPointLocation();
	CurrMovepPointIndex = (CurrMovepPointIndex + 1) % MovePoints.Num();
	return NextPoint;
}

FVector ANPCBase::GetStayPoint() const
{
	if (MovePoints.Num() == 0)
	{
		return GetActorLocation();
	}

	return StayPoint->GetPointLocation();
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

