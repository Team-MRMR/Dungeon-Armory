// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/AI/Task/BTTask_MoveToPoint.h"
#include "Characters/NPC/AI/LocationPoint.h"
#include "Characters/NPC/AI/NPCAIController.h"
#include "Characters/NPC/NPCBase.h"

#include "Characters/Core/Component/CharacterStatComponent.h"
#include "Characters/Core/Component/MovementControllerComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_MoveToPoint::UBTTask_MoveToPoint()
{
    NodeName = "NPC MoveToPoint"; // BT에서 보이는 이름
}

EBTNodeResult::Type UBTTask_MoveToPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    return EBTNodeResult::InProgress;
}

void UBTTask_MoveToPoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(NPCBBKeys::Target));
	if (!TargetActor)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	auto MovementController = Cast<UMovementControllerComponent>(Blackboard->GetValueAsObject(NPCBBKeys::MovementController));
	if (!MovementController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	auto* Stat = Cast<UCharacterStatComponent>(Blackboard->GetValueAsObject(NPCBBKeys::Stat));
	if (!Stat)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	MovementController->MoveToDestination(TargetActor->GetActorLocation(), Stat->AttackableDistance);
}

void UBTTask_MoveToPoint::OnMoveCompleted(UBehaviorTreeComponent* BTComp)
{
    FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
}
