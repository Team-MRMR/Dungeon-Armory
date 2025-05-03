// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/Tasks/BTTask_Chase.h"
#include "Characters/Mob/MobBase.h"
#include "Characters/Core/Component/MovementControllerComponent.h"
#include "AIController.h"

#include "GameFramework/Actor.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Navigation/PathFollowingComponent.h"

UBTTask_Chase::UBTTask_Chase()
{
    bNotifyTick = true;
    NodeName = TEXT("Mob Chase");

    // 기본적으로 Blackboard 키 자동 UI 지정
    BBkey_AcceptableRadius.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Chase, BBkey_AcceptableRadius));
}

void UBTTask_Chase::InitializeFromAsset(UBehaviorTree& BehaviorTreeAsset)
{
    Super::InitializeFromAsset(BehaviorTreeAsset);

    if (UBlackboardData* BlackboardAsset = BehaviorTreeAsset.BlackboardAsset)
    {
        BBkey_AcceptableRadius.ResolveSelectedKey(*BlackboardAsset);
    }
}

EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AcceptableRadius = BlackboardComp->GetValueAsFloat(BBkey_AcceptableRadius.SelectedKeyName);
    TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));
    if (TargetActor == nullptr)
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

void UBTTask_Chase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	MovementController->MoveToDestination(TargetActor->GetActorLocation(), AcceptableRadius);
}

void UBTTask_Chase::OnMoveCompleted(UBehaviorTreeComponent* BTComp)
{
    // Task 종료
    FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
}