// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Chase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"

UBTTask_Chase::UBTTask_Chase()
{
    NodeName = "Chase"; // BT에서 보이는 이름
}

EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject("Target"));
    if (!Target)
    {
        return EBTNodeResult::Failed;
    }

    AIController->MoveToActor(Target);

    return EBTNodeResult::Succeeded;
}