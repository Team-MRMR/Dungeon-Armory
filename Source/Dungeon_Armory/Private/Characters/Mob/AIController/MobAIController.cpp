// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/AIController/MobAIController.h"

#include "AI/Interface/IMovableTask.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"


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
