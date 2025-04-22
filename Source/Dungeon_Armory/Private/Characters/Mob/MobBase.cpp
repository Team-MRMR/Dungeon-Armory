// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/MobBase.h"
#include "Characters/Core/CharacterStatComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "AI/Team/TeamComponent.h"

// Sets default values
AMobBase::AMobBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ��Ʈ�ѷ� ȸ�� ���� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// �̵�	�������� ȸ���ϵ��� ����
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ���� ������Ʈ ����
	StatComponent = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("StatComponent"));

	// �� ������Ʈ ����
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
}

// Called when the game starts or when spawned
void AMobBase::BeginPlay()
{
	Super::BeginPlay();
	
}
