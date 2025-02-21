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
    // 비헤이비어 트리와 블랙보드 컴포넌트 생성
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // AI 감지 시스템 초기화
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // 감지 범위 설정
    SightConfig->SightRadius = 2000.0f; // AI가 감지할 최대 거리
    SightConfig->LoseSightRadius = 2500.0f; // 감지 후 잃어버리는 거리
    SightConfig->PeripheralVisionAngleDegrees = 120.0f; // 시야각 120도
    SightConfig->SetMaxAge(5.0f); // 감지 정보 유지 시간

    // 감지 설정 적용
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

            // 초기 블랙보드 값 설정
            BlackboardComponent->SetValueAsVector("HomeLocation", Enemy->GetActorLocation());
        }
    }
}

// 감지 이벤트 처리
void AEnemyAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (!BlackboardComponent)
    {
        return; // 블랙보드가 없으면 종료
    }

    bool bIsVisible = Stimulus.WasSuccessfullySensed();

    // 블랙보드 값 설정
    BlackboardComponent->SetValueAsBool("IsAlerted", bIsVisible);
    BlackboardComponent->SetValueAsObject("Target", bIsVisible ? Actor : nullptr);

    UE_LOG(LogTemp, Warning, TEXT("AI Perception: %s detected!"), bIsVisible ? TEXT("Target") : TEXT("None"));
}
