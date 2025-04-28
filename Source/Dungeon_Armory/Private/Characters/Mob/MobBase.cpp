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

	// 컨트롤러 회전 제어 해제
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 컨트롤러 회전은 무시
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	// 이동	방향으로 회전하도록 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 회전 속도 설정 (원하는 속도로 조정)
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	// 스탯 컴포넌트 생성
	StatComponent = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("StatComponent"));

	// 팀 컴포넌트 생성
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
	OutLocation = GetMesh()->GetSocketLocation(FName("EyeSocket"));	// 머리 위치를 기준으로 시점 설정
	OutRotation = GetMesh()->GetSocketRotation(FName("EyeSocket"));	// 머리 위치를 기준으로 시점 설정
}
