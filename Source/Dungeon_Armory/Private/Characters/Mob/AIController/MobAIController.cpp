// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/AIController/MobAIController.h"
#include "Characters/Mob/Component/MobAttackComponent.h"
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
    PrimaryActorTick.bCanEverTick = true;
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
    if (ACharacter* MobCharacter = Cast<ACharacter>(InPawn))
    {
        if (AMobBase* MobBase = Cast<AMobBase>(MobCharacter))
        {
            StatComponent = MobBase->FindComponentByClass<UCharacterStatComponent>();

			MovementControllerComponent = MobBase->FindComponentByClass<UMovementControllerComponent>();
			MovementControllerComponent->OnMovementCompleted.AddDynamic(this, &AMobAIController::OnMovementCompleted);

			MobAttackComponent = MobBase->FindComponentByClass<UMobAttackComponent>();
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

    if (!BlackboardComponent)
        return;

    if (!DetectedPlayer)
        return;

    // �÷��̾���� �Ÿ� ���
    FVector MobLocation = GetPawn()->GetActorLocation();
    FVector PlayerLocation = DetectedPlayer->GetActorLocation();
    float Distance = FVector::Dist2D(MobLocation, PlayerLocation);

    if (Distance <= StatComponent->AttackableDistance)  // ���� ���� �����
    {
        BlackboardComponent->SetValueAsEnum(MobStateKey, static_cast<uint8>(EMobState::Battle));
    }
    else if (Distance <= StatComponent->SightRadius)    // �߰� ���� �����
    {
        BlackboardComponent->SetValueAsEnum(MobStateKey, static_cast<uint8>(EMobState::Chase));
    }
    else    // �߰� ���� ���̶��
    {
        BlackboardComponent->SetValueAsEnum(MobStateKey, static_cast<uint8>(EMobState::Patrol));
    }
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
	// --- ���� ���� Ű�� ---
    BlackboardComponent->SetValueAsEnum(BBKeys::MobState, static_cast<uint8>(EMobState::Patrol));

	// --- ������Ʈ ���� Ű�� ---
	BlackboardComponent->SetValueAsObject(BBKeys::Stat, StatComponent);
	BlackboardComponent->SetValueAsObject(BBKeys::MovementController, MovementControllerComponent);
	BlackboardComponent->SetValueAsObject(BBKeys::AttackComponent, MobAttackComponent);

    // --- �Ÿ� ���� Ű�� ---
    BlackboardComponent->SetValueAsVector(BBKeys::HomeLocation, GetPawn()->GetActorLocation());
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

    bool bDetectedTarget = Stimulus.WasSuccessfullySensed();
    if (bDetectedTarget)
    {
        // �÷��̾ ������
		OnMovementCompleted();
        DetectedPlayer = Actor;
        BlackboardComponent->SetValueAsObject("Target", Actor);

    }
    else if(DetectedPlayer == Actor)
    {
        // �÷��̾ ��ħ
        OnMovementCompleted();
        DetectedPlayer = nullptr;
        BlackboardComponent->SetValueAsObject("Target", nullptr);
    }

    StopMovement();
    // ���� ���� ���� BTTask �ߴ� (Patrol Task �ߴ�)
    if (BehaviorTreeComponent)
    {
        BehaviorTreeComponent->RequestExecution(EBTNodeResult::Type::Aborted);
    }
}
