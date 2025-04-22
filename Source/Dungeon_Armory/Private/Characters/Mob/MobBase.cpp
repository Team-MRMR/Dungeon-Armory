// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/MobBase.h"

#include "AI/Team/TeamComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AMobBase::AMobBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// �� ������Ʈ ����
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

	//// ���� �ð��� ������ ���� �ӵ��� ����
	//GetWorldTimerManager().SetTimer(SpeedResetTimer, this, &ANPCCharacter::ResetSpeed, Duration, false);
}

void AMobBase::SetMovementSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}
