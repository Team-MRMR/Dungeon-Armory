// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/MobBase.h"
#include "Characters/Core/CharacterStatComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "AI/Team/TeamComponent.h"

// Sets default values
AMobBase::AMobBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 컨트롤러 회전 제어 해제
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 이동	방향으로 회전하도록 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 스탯 컴포넌트 생성
	StatComponent = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("StatComponent"));

	// 팀 컴포넌트 생성
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
}

// Called when the game starts or when spawned
void AMobBase::BeginPlay()
{
	Super::BeginPlay();
	
}
