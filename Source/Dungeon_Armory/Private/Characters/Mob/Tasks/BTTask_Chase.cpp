// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/Tasks/BTTask_Chase.h"
#include "GameFramework/Actor.h"
#include "AIController.h"

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
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));
    if (TargetActor == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    float AcceptableRadius = BlackboardComp->GetValueAsFloat(BBkey_AcceptableRadius.SelectedKeyName);

    FAIMoveRequest MoveRequest;
    MoveRequest.SetGoalActor(TargetActor);
    MoveRequest.SetAcceptanceRadius(AcceptableRadius);

    EPathFollowingRequestResult::Type RequestResultID = AIController->MoveTo(MoveRequest);

    if (RequestResultID == EPathFollowingRequestResult::Failed)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_Chase::OnMoveCompleted(UBehaviorTreeComponent* BTComp)
{
    // Task 종료
    FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
}