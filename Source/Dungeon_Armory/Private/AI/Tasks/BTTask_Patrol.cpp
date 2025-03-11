// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Patrol.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

#include "AITypes.h"                            // FAIRequestID, EPathFollowingRequestResult
#include "Navigation/PathFollowingComponent.h"  // EPathFollowingResult

UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = "Patrol"; // BT에서 보이는 이름
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& BehaviorTreeCmp, uint8* NodeMemory)
{
    
}

void UBTTask_Patrol::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    
}
