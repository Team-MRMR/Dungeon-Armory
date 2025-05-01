// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Component/CharacterStatComponent.h"

#include "Characters/Mob/MobBase.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	if (AMobBase* Mob = Cast<AMobBase>(GetOwner()))
	{
		OwnerCharacter = Mob;
	}

	CurrentHealth = MaxHealth;
}

// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
void UCharacterStatComponent::ApplySpeedModifier(float SpeedMultiplier, float Duration)
{
	//float NewSpeed = BaseSpeed * SpeedMultiplier;
	//SetMovementSpeed(NewSpeed);

	//// ���� �ð��� ������ ���� �ӵ��� ����
	//GetWorldTimerManager().SetTimer(SpeedResetTimer, this, &ANPCCharacter::ResetSpeed, Duration, false);
}

void UCharacterStatComponent::ResetSpeed()
{
	SetSpeed(BaseSpeed);
}

void UCharacterStatComponent::SetSpeed(float NewSpeed)
{
	if (OwnerCharacter)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	}
}

float UCharacterStatComponent::GetSpeedForState(EMobState State) const
{
	switch (State)
	{
	case EMobState::Idle:    return BaseSpeed * IdleSpeedOffset;
	case EMobState::Patrol:  return BaseSpeed * PatrolSpeedOffset;
	case EMobState::Chase:   return BaseSpeed * ChaseSpeedOffset;
	case EMobState::Battle:  return BaseSpeed * CombatSpeedOffset;
	case EMobState::Dead:    return BaseSpeed * DeadSpeedOffset;
	default:				 return BaseSpeed;
	}
}

void UCharacterStatComponent::SetSpeedForState(EMobState State)
{
	float ChangedSpeed = GetSpeedForState(State);
	SetSpeed(ChangedSpeed);
}

void UCharacterStatComponent::ApplyDamage(float DamageAmount)
{
	UE_LOG(LogTemp, Error, TEXT("Damage Amount: %f"), DamageAmount);
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
	UE_LOG(LogTemp, Error, TEXT("Current Health: %f"), CurrentHealth);
	IsDead();
}

bool UCharacterStatComponent::IsDead() const
{
	return CurrentHealth <= 0.f;
}
