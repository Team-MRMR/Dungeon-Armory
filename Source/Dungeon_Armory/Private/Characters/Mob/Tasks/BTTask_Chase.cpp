// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/Tasks/BTTask_Chase.h"
#include "Characters/Mob/MobBase.h"
#include "Characters/Core/Component/MovementControllerComponent.h"

#include "Characters/Mob/AIController/MobAIController.h"

#include "GameFramework/Actor.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Navigation/PathFollowingComponent.h"

UBTTask_Chase::UBTTask_Chase()
{
    bNotifyTick = true;
    NodeName = TEXT("Mob Chase");
}

void UBTTask_Chase::InitializeFromAsset(UBehaviorTree& BehaviorTreeAsset)
{
    Super::InitializeFromAsset(BehaviorTreeAsset);
}

EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    return EBTNodeResult::InProgress;
}

void UBTTask_Chase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
    {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

	AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(BBKeys::Target));
	if (!TargetActor)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	auto MovementController = Cast<UMovementControllerComponent>(Blackboard->GetValueAsObject(BBKeys::MovementController));
	if (!MovementController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	auto* Stat = Cast<UCharacterStatComponent>(Blackboard->GetValueAsObject(BBKeys::Stat));
	if (!Stat)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	MovementController->MoveToDestination(TargetActor->GetActorLocation(), Stat->AttackableDistance);
}

void UBTTask_Chase::OnMoveCompleted(UBehaviorTreeComponent* BTComp)
{
	//auto MobAIController = Cast<AMobAIController>(BTComp->GetAIOwner());
	//if (!MobAIController)
	//	return;
	//
	//MobAIController->SetMobState(EMobState::Battle);

    // Task ����
    FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
}