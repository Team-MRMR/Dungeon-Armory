// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCBase.h"
#include "Characters/NPC/NPCAIController.h"

#include "Manager/TeamManager.h"



// Sets default values
ANPCBase::ANPCBase()
{
	// Create Team Component and 
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

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

