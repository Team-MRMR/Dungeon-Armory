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
    NodeName = "Patrol"; // BT에서 보이는 이름
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

    return EBTNodeResult::InProgress; // 이동 완료 후 OnMoveCompleted에서 처리
}

void UBTTask_Patrol::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    AAIController* AIController = Cast<AAIController>(BehaviorTreeCmpt->GetAIOwner());
    if (AIController)
    {
        ANPCAIController* NPCAIController = Cast<ANPCAIController>(AIController);
        if (NPCAIController)
        {
            NPCAIController->SetNPCState(ENPCStates::Stay); // Idle 상태로 변경
        }
    }

    FinishLatentTask(*BehaviorTreeCmpt, EBTNodeResult::Succeeded);
}
