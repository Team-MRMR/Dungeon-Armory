// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Stay.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Stay::UBTTask_Stay()
{
    NodeName = TEXT("Stay");
}

EBTNodeResult::Type UBTTask_Stay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 블랙보드 값 변경 감지를 위한 설정
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        // 특정 블랙보드 키가 변경되었을 때 Stay를 종료하도록 설정
        FBlackboard::FKey ExitStayKey = BlackboardComp->GetKeyID("bShouldExitStay");
        if (ExitStayKey != FBlackboard::InvalidKey)
        {
            // 올바른 함수 포인터를 사용하여 델리게이트 바인딩
            BlackboardComp->RegisterObserver(ExitStayKey, this, FOnBlackboardChangeNotification::CreateUObject(this, &UBTTask_Stay::OnBlackboardValueChanged));
        }
    }

    // Stay 상태 유지
    return EBTNodeResult::InProgress;
}

EBlackboardNotificationResult UBTTask_Stay::OnBlackboardValueChanged(const UBlackboardComponent& Blackboard, FBlackboard::FKey Key)
{
    if (Blackboard.GetValueAsBool("bShouldExitStay"))
    {
        // Stay 상태 종료
        FinishLatentTask(*Cast<UBehaviorTreeComponent>(Blackboard.GetOwner()), EBTNodeResult::Succeeded);
        return EBlackboardNotificationResult::RemoveObserver;
    }

    return EBlackboardNotificationResult::ContinueObserving;
}


void UBTTask_Stay::OnAbort(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Stay 상태가 강제로 중단될 때 호출됨
    UE_LOG(LogTemp, Warning, TEXT("Stay Task Aborted!"));
}
