// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Patrol.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

#include "AITypes.h"                    // FAIRequestID, EPathFollowingRequestResult
#include "Navigation/PathFollowingComponent.h"  // EPathFollowingResult

UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = "Patrol"; // BT에서 보이는 이름

    bNotifyTick = false; // Tick이 필요하지 않음
    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& BehaviorTreeCmp, uint8* NodeMemory)
{
    BehaviorTreeComponent = &BehaviorTreeCmp;

    AAIController* AIController = BehaviorTreeCmp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = BehaviorTreeCmp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(AIPawn);
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    FVector Origin = AIPawn->GetActorLocation();
    FNavLocation PatrolLocation;

    if (NavSys->GetRandomPointInNavigableRadius(Origin, 500.0f, PatrolLocation))
    {
        BlackboardComp->SetValueAsVector("PatrolPoint", PatrolLocation.Location);

        FAIRequestID RequestID;
        EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(PatrolLocation.Location);

        if (Result == EPathFollowingRequestResult::RequestSuccessful)
        {
            AIController->ReceiveMoveCompleted.AddDynamic(this, &UBTTask_Patrol::OnMoveCompleted);
            return EBTNodeResult::InProgress;
        }
    }

    return EBTNodeResult::Failed;
}

void UBTTask_Patrol::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    UE_LOG(LogTemp, Warning, TEXT("Move Completed: %d"), static_cast<int32>(Result));

    if (Result == EPathFollowingResult::Success)
    {
        FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
    }
    else
    {
        FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Failed);
    }
}
