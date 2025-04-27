// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/MobBase.h"

#include "Characters/Core/CharacterStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Team/TeamComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"

const FName AMobBase::MobStateKey(TEXT("MobState"));

// Sets default values
AMobBase::AMobBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ��Ʈ�ѷ� ȸ�� ���� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ��Ʈ�ѷ� ȸ���� ����
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	// �̵�	�������� ȸ���ϵ��� ����
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ȸ�� �ӵ� ���� (���ϴ� �ӵ��� ����)
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	// ���� ������Ʈ ����
	StatComponent = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("StatComponent"));

	// �� ������Ʈ ����
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
	TeamComponent->SetTeamType(ETeamType::Mob);
}

// Called when the game starts or when spawned
void AMobBase::BeginPlay()
{
	Super::BeginPlay();
	
	MobAIController = Cast<AAIController>(GetController());
	if (MobAIController)
	{
		MobBlackboardComponent = MobAIController->GetBlackboardComponent();
	}
}

void AMobBase::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation(FName("EyeSocket"));	// �Ӹ� ��ġ�� �������� ���� ����
	OutRotation = GetMesh()->GetSocketRotation(FName("EyeSocket"));	// �Ӹ� ��ġ�� �������� ���� ����
}

void AMobBase::ApplySpeedModifier(float SpeedMultiplier, float Duration)
{
	//float NewSpeed = BaseSpeed * SpeedMultiplier;
	//SetMovementSpeed(NewSpeed);

	//// ���� �ð��� ������ ���� �ӵ��� ����
	//GetWorldTimerManager().SetTimer(SpeedResetTimer, this, &ANPCCharacter::ResetSpeed, Duration, false);
}

void AMobBase::ResetSpeed()
{
	if (StatComponent)
	{
		SetSpeed(StatComponent->BaseSpeed);
	}
}

void AMobBase::SetSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

float AMobBase::GetSpeedForState(EMobState State) const
{
	switch (State)
	{
	case EMobState::Idle:    return StatComponent->BaseSpeed * StatComponent->IdleSpeedOffset;
	case EMobState::Patrol:  return StatComponent->BaseSpeed * StatComponent->PatrolSpeedOffset;
	case EMobState::Chase:   return StatComponent->BaseSpeed * StatComponent->ChaseSpeedOffset;
	case EMobState::Battle:  return StatComponent->BaseSpeed * StatComponent->CombatSpeedOffset;
	case EMobState::Dead:    return StatComponent->BaseSpeed * StatComponent->DeadSpeedOffset;
	default:				 return StatComponent->BaseSpeed;
	}
}

void AMobBase::SetSpeedForState(EMobState State)
{
	float ChangedSpeed = GetSpeedForState(State);
	SetSpeed(ChangedSpeed);
}

void AMobBase::SetMobState(EMobState NewState)
{
	if (CurrentState == NewState)
	{
		return;  // ���� ���·��� ������ ����
	}

	CurrentState = NewState;

	// �����忡 ���� ������Ʈ
	if (MobBlackboardComponent)
	{
		MobBlackboardComponent->SetValueAsEnum(MobStateKey, static_cast<uint8>(NewState));
	}
}

void AMobBase::ApplyDamage(float DamageAmount)
{
	StatComponent->CurrentHealth = FMath::Clamp(StatComponent->CurrentHealth - DamageAmount, 0.f, StatComponent->MaxHealth);
}

bool AMobBase::IsDead() const
{
	return StatComponent->CurrentHealth <= 0.f;
}