// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/Tasks/BTTask_Patrol.h"

#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Mob/MobBase.h"
#include "Characters/Core/Component/MovementControllerComponent.h"

#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	bNotifyTick = true;

	NodeName = TEXT("Mob Patrol");

	// 기본적으로 Blackboard 키 자동 UI 지정
	BBkey_HomeLocation.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Patrol, BBkey_HomeLocation));
	BBkey_PatrolRadius.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Patrol, BBkey_PatrolRadius));
	BBkey_AcceptableRadius.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Patrol, BBkey_AcceptableRadius));
}

void UBTTask_Patrol::InitializeFromAsset(UBehaviorTree& BehaviorTreeAsset)
{
	Super::InitializeFromAsset(BehaviorTreeAsset);

	if (UBlackboardData* BlackboardAsset = BehaviorTreeAsset.BlackboardAsset)
	{
		BBkey_HomeLocation.ResolveSelectedKey(*BlackboardAsset);
		BBkey_PatrolRadius.ResolveSelectedKey(*BlackboardAsset);
		BBkey_AcceptableRadius.ResolveSelectedKey(*BlackboardAsset);
	}
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	FVector HomeLocation = BlackboardComp->GetValueAsVector(BBkey_HomeLocation.SelectedKeyName);
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(OwnerComp.GetWorld());
	if (!NavSys)
	{
		return EBTNodeResult::Failed;
	}

	AcceptableRadius = BlackboardComp->GetValueAsFloat(BBkey_AcceptableRadius.SelectedKeyName);

	float PatrolRadius = BlackboardComp->GetValueAsFloat(BBkey_PatrolRadius.SelectedKeyName);
	bool bFound = NavSys->GetRandomPointInNavigableRadius(HomeLocation, PatrolRadius, RandomLocation);
	if (!bFound)
	{
		return EBTNodeResult::Failed;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	AMobBase* MobBase = Cast<AMobBase>(Pawn);
	if (!MobBase)
	{
		return EBTNodeResult::Failed;
	}

	MovementController = MobBase->FindComponentByClass<UMovementControllerComponent>();
	if (!MovementController)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	MovementController->MoveToDestination(RandomLocation.Location, AcceptableRadius);
}

void UBTTask_Patrol::OnMoveCompleted(UBehaviorTreeComponent* BTComp)
{
	// Task 종료
	FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
}