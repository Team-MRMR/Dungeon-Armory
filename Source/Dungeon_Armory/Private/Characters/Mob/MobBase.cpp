// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/MobBase.h"

#include "Characters/Core/CharacterStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Team/TeamComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"

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
}

void AMobBase::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation(FName("EyeSocket"));	// �Ӹ� ��ġ�� �������� ���� ����
	OutRotation = GetMesh()->GetSocketRotation(FName("EyeSocket"));	// �Ӹ� ��ġ�� �������� ���� ����
}
