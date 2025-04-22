// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/Tasks/BTTask_Patrol.h"

#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol Around Home");

	// �⺻������ Blackboard Ű �ڵ� UI ����
	HomeLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Patrol, HomeLocationKey));
	//TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Patrol, TargetLocationKey));
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	FVector HomeLocation = BlackboardComp->GetValueAsVector(HomeLocationKey.SelectedKeyName);
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(OwnerComp.GetWorld());
	if (!NavSys)
	{
		return EBTNodeResult::Failed;
	}

	// �׺���̼� ������ ���� ��ġ ����
	FNavLocation RandomLocation;
	bool bFound = NavSys->GetRandomPointInNavigableRadius(HomeLocation, PatrolRadius, RandomLocation);
	if (!bFound)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, RandomLocation.Location);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	FAIRequestID MoveRequestID = AIController->MoveToLocation(RandomLocation.Location, AcceptanceRadius);


	if (!MoveRequestID.IsValid())
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::OnMoveCompleted(UBehaviorTreeComponent* BTComp)
{
	// Task ����
	FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
}
