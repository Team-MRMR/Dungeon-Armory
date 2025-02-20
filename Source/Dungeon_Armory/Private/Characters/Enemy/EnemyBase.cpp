// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyBase.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // �⺻ AI ���¸� Idle�� ����
    CurrentState = EEnemyState::Idle;

    // AI ���� �ý��� �ʱ�ȭ
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // ���� ���� ����
    SightConfig->SightRadius = 1000.0f; // AI�� ������ �ִ� �Ÿ�
    SightConfig->LoseSightRadius = 1200.0f; // ���� �� �Ҿ������ �Ÿ�
    SightConfig->PeripheralVisionAngleDegrees = 90.0f; // �þ߰� 90��
    SightConfig->SetMaxAge(5.0f); // ���� ���� ���� �ð�

    // ���� ���� ����
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

    // Chase ���·� ����
    SetEnemyState(EEnemyState::Chase);
}

// ���� �̺�Ʈ ó��
void AEnemyBase::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
        if (Blackboard)
        {
            // ���� ���� ���� Ȯ��
            bool bIsVisible = Stimulus.WasSuccessfullySensed();
            Blackboard->SetValueAsBool("IsAlerted", bIsVisible);
            Blackboard->SetValueAsObject("Target", bIsVisible ? Actor : nullptr);
        }
    }
}
