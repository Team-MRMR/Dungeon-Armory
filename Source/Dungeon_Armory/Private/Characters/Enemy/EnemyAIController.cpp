// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyAIController.h"
#include "Characters/Enemy/EnemyBase.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

AEnemyAIController::AEnemyAIController()
{
    // �����̺�� Ʈ���� ������ ������Ʈ ����
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // AI ���� �ý��� �ʱ�ȭ
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // ���� ���� ����
    SightConfig->SightRadius = 2000.0f; // AI�� ������ �ִ� �Ÿ�
    SightConfig->LoseSightRadius = 2500.0f; // ���� �� �Ҿ������ �Ÿ�
    SightConfig->PeripheralVisionAngleDegrees = 120.0f; // �þ߰� 120��
    SightConfig->SetMaxAge(5.0f); // ���� ���� ���� �ð�

    // ���� ���� ����
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

    AIPerceptionComponent->ConfigureSense(*SightConfig);
    AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceived);
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AEnemyAIController::SetBlackboardKey(FName KeyName, UObject* Value)
{
    if (BlackboardComponent)
    {
        BlackboardComponent->SetValueAsObject(KeyName, Value);
    }
}

void AEnemyAIController::SetBlackboardKeyBool(FName KeyName, bool bValue)
{
    if (BlackboardComponent)
    {
        BlackboardComponent->SetValueAsBool(KeyName, bValue);
    }
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (AEnemyBase* Enemy = Cast<AEnemyBase>(InPawn))
    {
        if (BehaviorTree)
        {
            UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
            RunBehaviorTree(BehaviorTree);

            // �ʱ� ������ �� ����
            BlackboardComponent->SetValueAsVector("HomeLocation", Enemy->GetActorLocation());
        }
    }
}

// ���� �̺�Ʈ ó��
void AEnemyAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (!BlackboardComponent)
    {
        return; // �����尡 ������ ����
    }

    bool bIsVisible = Stimulus.WasSuccessfullySensed();

    // ������ �� ����
    BlackboardComponent->SetValueAsBool("IsAlerted", bIsVisible);
    BlackboardComponent->SetValueAsObject("Target", bIsVisible ? Actor : nullptr);

    UE_LOG(LogTemp, Warning, TEXT("AI Perception: %s detected!"), bIsVisible ? TEXT("Target") : TEXT("None"));
}
