// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Patrol.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = "Patrol"; // BT에서 보이는 이름
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
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
        AIController->MoveToLocation(PatrolLocation);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
