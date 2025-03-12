// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/BTTask_Patrol.h"
#include "AIController.h"
#include "AITypes.h"                            // FAIRequestID, EPathFollowingRequestResult
#include "Navigation/PathFollowingComponent.h"  // EPathFollowingResult
#include "NavigationSystem.h"
#include "Characters/NPC/NPCAIController.h"
#include "Characters/NPC/NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = "Patrol"; // BT���� ���̴� �̸�
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ANPCAIController* NPCAIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
    if (NPCAIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ANPCBase* NPC = Cast<ANPCBase>(NPCAIController->GetPawn());
    if (NPC == nullptr)
    {
        return EBTNodeResult::Failed;
    }

	BehaviorTreeCmpt = &OwnerComp;

    FVector PatrolLocation = NPC->GetNextPatrolPoint();

    NPCAIController->MoveToLocation(PatrolLocation);
    NPCAIController->ReceiveMoveCompleted.AddDynamic(this, &UBTTask_Patrol::OnMoveCompleted);

    return EBTNodeResult::InProgress; // �̵� �Ϸ� �� OnMoveCompleted���� ó��
}

void UBTTask_Patrol::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    AAIController* AIController = Cast<AAIController>(BehaviorTreeCmpt->GetAIOwner());
    if (AIController)
    {
        ANPCAIController* NPCAIController = Cast<ANPCAIController>(AIController);
        if (NPCAIController)
        {
            NPCAIController->SetNPCState(ENPCStates::Stay); // Idle ���·� ����
        }
    }

    FinishLatentTask(*BehaviorTreeCmpt, EBTNodeResult::Succeeded);
}
