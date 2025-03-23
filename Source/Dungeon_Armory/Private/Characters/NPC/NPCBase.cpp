// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCBase.h"
#include "Characters/NPC/MovePoint.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "AI/Team/TeamComponent.h"

#include "Manager/InGameTimeManager.h"

/*
* Functions (Unreal)
*/

ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// ÆÀ ÄÄÆ÷³ÍÆ® »ý¼º
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
}

/*
* Functions (Movement)
*/

void ANPCBase::SetMovementSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

/*
* Functions (Team)
*/

FGenericTeamId ANPCBase::GetGenericTeamId() const
{
	return TeamComponent->GetGenericTeamId();
}

void ANPCBase::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamComponent->SetTeamType(static_cast<ETeamType>(NewTeamID.GetId()));
}

/*
* Functions (Behavior Tree)
*/

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
	if (!StayPoint)
	{
		return GetActorLocation();
	}

	return StayPoint->GetPointLocation();
}
