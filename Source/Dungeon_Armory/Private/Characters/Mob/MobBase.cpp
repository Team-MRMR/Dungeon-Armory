// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/MobBase.h"

#include "Characters/Core/Component/CharacterStatComponent.h"
#include "Characters/Core/Component/MobAttackComponent.h"
#include "Characters/Core/Component/MovementControllerComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Team/TeamComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"

// Sets default values
AMobBase::AMobBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ���� ������Ʈ ����
	StatComponent = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("StatComponent"));

	// ���� ������Ʈ ����
	AttackComponent = CreateDefaultSubobject<UMobAttackComponent>(TEXT("AttackComponent"));

	// �̵� ��Ʈ�ѷ� ������Ʈ ����
	MovementControllerComponent = CreateDefaultSubobject<UMovementControllerComponent>(TEXT("MovementControllerComponent"));

	// �� ������Ʈ ����
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
	TeamComponent->SetTeamType(ETeamType::Mob);

	// (Pawn) ��Ʈ�ѷ� ȸ�� ���� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ��Ʈ�ѷ� ȸ���� ����
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	// �̵�	�������� ȸ���ϵ��� ����
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ȸ�� �ӵ� ���� (���ϴ� �ӵ��� ����)
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	GetCharacterMovement()->UseAccelerationForPathFollowing();
}

// Called when the game starts or when spawned
void AMobBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = StatComponent->BaseSpeed;
}

void AMobBase::Tick(float DeltaSeconds)
{
}

void AMobBase::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation(FName("EyeSocket"));	// �Ӹ� ��ġ�� �������� ���� ����
	OutRotation = GetMesh()->GetSocketRotation(FName("EyeSocket"));	// �Ӹ� ��ġ�� �������� ���� ����
}

void AMobBase::ReceiveDamage(float DamageAmount)
{
	if (StatComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("MobBase::ReceiveDamage()"));
		StatComponent->ApplyDamage(DamageAmount);
	}
}
