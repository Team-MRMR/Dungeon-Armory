// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyBase.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // �⺻ AI ���¸� Idle�� ����
    CurrentState = EEnemyState::Idle;

    // PawnSensingComponent ����
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
    if (PawnSensingComponent)
    {
        PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyBase::OnSeePlayer);
        PawnSensingComponent->SetPeripheralVisionAngle(60.0f); // 60�� �þ߰� ����
    }

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::SetEnemyState(EEnemyState NewState)
{
    if (CurrentState == NewState)
    {
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Enemy state changed from [%d]to: [%d]"),
        static_cast<int32>(CurrentState), static_cast<int32>(NewState));

    CurrentState = NewState;
}

void AEnemyBase::OnSeePlayer(APawn* Pawn)
{
    if (!Pawn)
    {
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Player detected!"));

    // Chase ���·� ����
    SetEnemyState(EEnemyState::Chase);
}
