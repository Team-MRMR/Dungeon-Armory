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
    // ������ �� ���� ������ ���� ����
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        // Ư�� ������ Ű�� ����Ǿ��� �� Stay�� �����ϵ��� ����
        FBlackboard::FKey ExitStayKey = BlackboardComp->GetKeyID("bShouldExitStay");
        if (ExitStayKey != FBlackboard::InvalidKey)
        {
            // �ùٸ� �Լ� �����͸� ����Ͽ� ��������Ʈ ���ε�
            BlackboardComp->RegisterObserver(ExitStayKey, this, FOnBlackboardChangeNotification::CreateUObject(this, &UBTTask_Stay::OnBlackboardValueChanged));
        }
    }

    // Stay ���� ����
    return EBTNodeResult::InProgress;
}

EBlackboardNotificationResult UBTTask_Stay::OnBlackboardValueChanged(const UBlackboardComponent& Blackboard, FBlackboard::FKey Key)
{
    if (Blackboard.GetValueAsBool("bShouldExitStay"))
    {
        // Stay ���� ����
        FinishLatentTask(*Cast<UBehaviorTreeComponent>(Blackboard.GetOwner()), EBTNodeResult::Succeeded);
        return EBlackboardNotificationResult::RemoveObserver;
    }

    return EBlackboardNotificationResult::ContinueObserving;
}


void UBTTask_Stay::OnAbort(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Stay ���°� ������ �ߴܵ� �� ȣ���
    UE_LOG(LogTemp, Warning, TEXT("Stay Task Aborted!"));
}
