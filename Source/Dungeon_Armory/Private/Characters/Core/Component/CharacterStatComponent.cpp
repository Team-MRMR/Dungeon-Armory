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
}

// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	auto World = GetWorld();
	if (World)
	{
		AttackStamina.Initialize(World);
		SkillStamina.Initialize(World);
		LoggingStamina.Initialize(World);
		MiningStamina.Initialize(World);
	}

	SetSpeed(BaseSpeed);
	
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
	case EMobState::Idle:
		return BaseSpeed * IdleSpeedFactor;

	case EMobState::Patrol:
		return BaseSpeed * PatrolSpeedFactor;

	case EMobState::Chase:
	case EMobState::Battle:
		return BaseSpeed * ChaseSpeedFactor;

	case EMobState::Dead:
		return BaseSpeed * DeadSpeedFactor;

	default:
		return BaseSpeed;
	}
}

void UCharacterStatComponent::ConsumeAttackStamina()
{
	const float ConsumptionStamina = AttackStamina.Consumption;
	AttackStamina.Consume(ConsumptionStamina);
}

void UCharacterStatComponent::ConsumeSkillStamina()
{
	const float ConsumptionStamina = SkillStamina.Consumption;
	SkillStamina.Consume(ConsumptionStamina);
}

void UCharacterStatComponent::ConsumeLoggingStamina()
{
	const float ConsumptionStamina = LoggingStamina.Consumption;
	LoggingStamina.Consume(ConsumptionStamina);
}

void UCharacterStatComponent::ConsumeMiningStamina()
{
	const float ConsumptionStamina = MiningStamina.Consumption;
	MiningStamina.Consume(ConsumptionStamina);
}

void UCharacterStatComponent::SetSpeedForState(EMobState State)
{
	float ChangedSpeed = GetSpeedForState(State);
	SetSpeed(ChangedSpeed);
}

void UCharacterStatComponent::ApplyDamage(const float DamageAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
}