// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyBase.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // 기본 AI 상태를 Idle로 설정
    CurrentState = EEnemyState::Idle;

    // AI 감지 시스템 초기화
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // 감지 범위 설정
    SightConfig->SightRadius = 1000.0f; // AI가 감지할 최대 거리
    SightConfig->LoseSightRadius = 1200.0f; // 감지 후 잃어버리는 거리
    SightConfig->PeripheralVisionAngleDegrees = 90.0f; // 시야각 90도
    SightConfig->SetMaxAge(5.0f); // 감지 정보 유지 시간

    // 감지 설정 적용
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

    AIPerception->ConfigureSense(*SightConfig);
    AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
    AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyBase::OnTargetPerceived);

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

    // Chase 상태로 변경
    SetEnemyState(EEnemyState::Chase);
}

// 감지 이벤트 처리
void AEnemyBase::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
        if (Blackboard)
        {
            // 감지 성공 여부 확인
            bool bIsVisible = Stimulus.WasSuccessfullySensed();
            Blackboard->SetValueAsBool("IsAlerted", bIsVisible);
            Blackboard->SetValueAsObject("Target", bIsVisible ? Actor : nullptr);
        }
    }
}
