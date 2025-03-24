// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_ChangeSpeed.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/NPC/NPCBase.h"
#include "Characters/NPC/NPCAIController.h"

UBTTask_ChangeSpeed::UBTTask_ChangeSpeed()
{
	NodeName = "ChangeSpeed";
}

EBTNodeResult::Type UBTTask_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto NPCController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	if (!NPCController)
	{
		return EBTNodeResult::Failed;
	}

	auto* NPC = Cast<ANPCBase>(NPCController->GetPawn());
	if (!NPC)
	{
		return EBTNodeResult::Failed;
	}

	float NewSpeed;
	ENPCStates targetState = static_cast<ENPCStates>(OwnerComp.GetBlackboardComponent()->GetValueAsEnum("NPCState"));

	switch (targetState)
	{
	case ENPCStates::MoveToPoint:
		NewSpeed = 250.0f;
		break;
	case ENPCStates::RoamToPoints:
	case ENPCStates::Chase:
		NewSpeed = 500.0f;
		break;
	case ENPCStates::Return:
		NewSpeed = 1000.0f;
		break;
	default:
		break;
	}

    NPC->SetMovementSpeed(NewSpeed);

    return EBTNodeResult::Succeeded;
}
