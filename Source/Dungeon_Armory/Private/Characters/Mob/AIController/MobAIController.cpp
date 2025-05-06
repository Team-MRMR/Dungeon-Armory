// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/AIController/MobAIController.h"
#include "Characters/Mob/MobBase.h"

#include "Characters/Core/Component/CharacterStatComponent.h"
#include "Characters/Core/Component/MovementControllerComponent.h"

#include "AI/Interface/IMovableTask.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

const FName AMobAIController::MobStateKey(TEXT("MobState"));

AMobAIController::AMobAIController()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMobAIController::BeginPlay()
{
    Super::BeginPlay();
}

void AMobAIController::OnPossess(APawn* InPawn)
{
    // �� ������Ʈ ����
    Super::OnPossess(InPawn);

    // ������Ʈ ���� �Ҵ�
    if (ACharacter* MobCharacter = Cast<ACharacter>(GetPawn()))
    {
        if (AMobBase* MobBase = Cast<AMobBase>(MobCharacter))
        {
            StatComponent = MobBase->FindComponentByClass<UCharacterStatComponent>();

			MovementControllerComponent = MobBase->FindComponentByClass<UMovementControllerComponent>();
			MovementControllerComponent->OnMovementCompleted.AddDynamic(this, &AMobAIController::OnMovementCompleted);
        }
    }

    // �����̺�� Ʈ�� ����
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // ������ ���� (AIController���� ������)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // ������ ���� �ʱ�ȭ
        if (BlackboardComponent)
        {
            InitializeBlackboardKeys();
        }

        // �����̺�� Ʈ�� ���� (�� �������� BehaviorTreeComponent�� �ڵ����� ������)
        RunBehaviorTree(BehaviorTree);

        // ���������� ������ BehaviorTreeComponent�� �����ͼ� ��� ������ �Ҵ�
        BehaviorTreeComponent = FindComponentByClass<UBehaviorTreeComponent>();
    }

    if (StatComponent)
    {
        if (SightConfig)
        {
            SightConfig->SightRadius = StatComponent->SightRadius;
            SightConfig->LoseSightRadius = StatComponent->LoseSightRadius;
            SightConfig->PeripheralVisionAngleDegrees = StatComponent->PeripheralVisionAngleDegrees;
            SightConfig->DetectionByAffiliation.bDetectEnemies = true;
            SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
            SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

            if (AIPerception)
            {
                // Perception ������Ʈ�� �þ� ���� ���� �߰�
                AIPerception->ConfigureSense(*SightConfig);

                // �켱������ ���� ���� �������� ����
                AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

                // ���� �̺�Ʈ �ݹ� ���
                AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMobAIController::OnTargetPerceived);
            }
        }
    }
}

void AMobAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMobAIController::SetMobState(EMobState NewState)
{
    EMobState CurrState = static_cast<EMobState>(BlackboardComponent->GetValueAsEnum(MobStateKey));
    if (CurrState == NewState)
    {
        return;  // ���� ���·��� ������ ����
    }

    // �����忡 ���� ������Ʈ
    if (BlackboardComponent)
    {
        BlackboardComponent->SetValueAsEnum(MobStateKey, static_cast<uint8>(NewState));
    }
}

void AMobAIController::InitializeBlackboardKeys()
{
    BlackboardComponent->SetValueAsVector("HomeLocation", GetPawn()->GetActorLocation());
    BlackboardComponent->SetValueAsEnum(BBKeys::MobState, static_cast<uint8>(EMobState::Patrol));

    BlackboardComponent->SetValueAsFloat(BBKeys::PatrolRadius, StatComponent->PatrolRadius);
    BlackboardComponent->SetValueAsFloat(BBKeys::AcceptableRadius, StatComponent->AcceptableRadius);
}

void AMobAIController::OnMovementCompleted()
{
    const UBTNode* ActiveNode = (BehaviorTreeComponent->GetActiveNode());
    if (ActiveNode)
    {
        // IIMovableTask �������̽��� ����Ͽ� �̵� �Ϸ� ó��
        IIMovableTask* MovableTask = const_cast<IIMovableTask*>(Cast<IIMovableTask>(ActiveNode));
        if (MovableTask)
        {
            MovableTask->OnMoveCompleted(BehaviorTreeComponent);
        }
    }
}

// ���� �̺�Ʈ ó��
void AMobAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor)
        return;

    if (!BlackboardComponent)
        return;

	UE_LOG(LogTemp, Warning, TEXT("Perceived Actor: %s"), *Actor->GetName());

    bool bDetectedTarget = Stimulus.WasSuccessfullySensed();
    if (bDetectedTarget)
    {
        // �÷��̾ ������
		OnMovementCompleted();
        DetectedPlayer = Actor;
        BlackboardComponent->SetValueAsObject("Target", Actor);
        BlackboardComponent->SetValueAsEnum(MobStateKey, static_cast<uint8>(EMobState::Chase));
    }
    else if(DetectedPlayer == Actor)
    {
        // �÷��̾ ��ħ
        OnMovementCompleted();
        DetectedPlayer = nullptr;
        BlackboardComponent->SetValueAsObject("Target", nullptr);
        BlackboardComponent->SetValueAsEnum(MobStateKey, static_cast<uint8>(EMobState::Patrol));
    }

    StopMovement();
    // ���� ���� ���� BT Task �ߴ� (Patrol Task �ߴ�)
    if (BehaviorTreeComponent)
    {
        BehaviorTreeComponent->RequestExecution(EBTNodeResult::Type::Aborted);
    }
}
