// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/CharacterStatComponent.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
	// ...
}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	// ...
	
}

float UCharacterStatComponent::GetSpeedForState(ECharacterState State) const
{
	switch (State)
	{
	case ECharacterState::Idle:    return IdleSpeed;
	case ECharacterState::Patrol:  return PatrolSpeed;
	case ECharacterState::Chase:   return ChaseSpeed;
	case ECharacterState::Battle:  return CombatSpeed;
	case ECharacterState::Dead:    return DeadSpeed;
	default:                       return PatrolSpeed;
	}
}

void UCharacterStatComponent::ApplyDamage(float DamageAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
}

bool UCharacterStatComponent::IsDead() const
{
	return CurrentHealth <= 0.f;
}


void UCharacterStatComponent::ResetSpeed()
{
	//SetMovementSpeed(BaseSpeed);
}

void UCharacterStatComponent::ApplySpeedModifier(float SpeedMultiplier, float Duration)
{
	//float NewSpeed = BaseSpeed * SpeedMultiplier;
	//SetMovementSpeed(NewSpeed);

	//// 일정 시간이 지나면 원래 속도로 복귀
	//GetWorldTimerManager().SetTimer(SpeedResetTimer, this, &ANPCCharacter::ResetSpeed, Duration, false);
}

void UCharacterStatComponent::SetMovementSpeed(float NewSpeed)
{
	//GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}