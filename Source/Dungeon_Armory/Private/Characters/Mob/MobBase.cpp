// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/MobBase.h"

#include "AI/Team/TeamComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AMobBase::AMobBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 팀 컴포넌트 생성
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
}

void AMobBase::BeginPlay()
{
}

FGenericTeamId AMobBase::GetGenericTeamId() const
{
	return TeamComponent->GetGenericTeamId();
}

void AMobBase::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamComponent->SetTeamType(static_cast<ETeamType>(NewTeamID.GetId()));
}

void AMobBase::ResetSpeed()
{
	//SetMovementSpeed(BaseSpeed);
}

void AMobBase::ApplySpeedModifier(float SpeedMultiplier, float Duration)
{
	//float NewSpeed = BaseSpeed * SpeedMultiplier;
	//SetMovementSpeed(NewSpeed);

	//// 일정 시간이 지나면 원래 속도로 복귀
	//GetWorldTimerManager().SetTimer(SpeedResetTimer, this, &ANPCCharacter::ResetSpeed, Duration, false);
}

void AMobBase::SetMovementSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}
