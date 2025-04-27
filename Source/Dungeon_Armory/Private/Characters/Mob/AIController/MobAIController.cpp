// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/AIController/MobAIController.h"

#include "AI/Interface/IMovableTask.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

AMobAIController::AMobAIController()
{
    PrimaryActorTick.bCanEverTick = false;

    SightConfig->SightRadius = 500.0f;
    SightConfig->LoseSightRadius = 700.f;
    SightConfig->PeripheralVisionAngleDegrees = 60.f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

    // Perception ������Ʈ�� �þ� ���� ���� �߰�
    AIPerception->ConfigureSense(*SightConfig);

    // �켱������ ���� ���� �������� ����
    AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

    // ���� �̺�Ʈ �ݹ� ���
    AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMobAIController::OnTargetPerceived);
}

void AMobAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AMobAIController::OnPossess(APawn* InPawn)
{
    // �� ������Ʈ ����
    Super::OnPossess(InPawn);

    // �����̺�� Ʈ�� ����
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // ������ ���� (AIController���� ������)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // ������ ���� �ʱ�ȭ
        if (BlackboardComponent)
        {
            BlackboardComponent->SetValueAsVector("HomeLocation", GetPawn()->GetActorLocation());
        }

        // �����̺�� Ʈ�� ���� (�� �������� BehaviorTreeComponent�� �ڵ����� ������)
        RunBehaviorTree(BehaviorTree);

        // ���������� ������ BehaviorTreeComponent�� �����ͼ� ��� ������ �Ҵ�
        BehaviorTreeComponent = FindComponentByClass<UBehaviorTreeComponent>();
    }
}

void AMobAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
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
        DetectedPlayer = Actor;
        BlackboardComponent->SetValueAsObject("Target", Actor);
    }
    else
    {
        // �÷��̾ ��ħ
        if (DetectedPlayer == Actor)
        {
            DetectedPlayer = nullptr;
            BlackboardComponent->SetValueAsObject("Target", nullptr);
            // ���¸� Idle�̳� Patrol�� �����ϴ� ���� �߰�
        }
    }
}
