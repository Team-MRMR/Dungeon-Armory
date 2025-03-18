// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/StaticNPCAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"

#include "AI/Tasks/BTTask_Stay.h"

#include "Manager/InGameTimeManager.h"

/***** Base Class *****/

AStaticNPCAIController::AStaticNPCAIController()
{

}

void AStaticNPCAIController::BeginPlay()
{
	Super::BeginPlay();

    // ���� �ð� �Ŵ��� ã��
    UInGameTimeManager* TimeManager = UInGameTimeManager::GetInstance();
    if (TimeManager)
    {
        // �ߺ� ���ε� ����
        if (!TimeManager->OnTimePeriodChanged.IsAlreadyBound(this, &AStaticNPCAIController::OnExitStay))
        {
            TimeManager->OnTimePeriodChanged.AddDynamic(this, &AStaticNPCAIController::OnExitStay);
        }
    }
}

void AStaticNPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

    // �����̺�� Ʈ�� ����
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // ������ ���� (AIController���� ������)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // ������ ���� �ʱ�ȭ
        if (BlackboardComponent)
        {
            BlackboardComponent->SetValueAsVector("HomeLocation", GetPawn()->GetActorLocation());
            SetNPCState(ENPCStates::Stay);

            // �����̺�� Ʈ�� ���� (�� �������� BehaviorTreeComponent�� �ڵ����� ������)
            RunBehaviorTree(BehaviorTree);

            // ���������� ������ BehaviorTreeComponent�� �����ͼ� ��� ������ �Ҵ�
            BehaviorTreeComponent = FindComponentByClass<UBehaviorTreeComponent>();
        }
    }
}

/***** Derived Class *****/

void AStaticNPCAIController::OnExitStay()
{
    if (GetNPCState() != ENPCStates::Stay)
    {
        return;
    }

    if (BehaviorTreeComponent)
    {
        const UBTNode* ActiveNode = BehaviorTreeComponent->GetActiveNode();
        if (ActiveNode)
        {
            UBTTask_Stay* StayTask = const_cast<UBTTask_Stay*>(Cast<UBTTask_Stay>(ActiveNode));
            if (StayTask)
            {
                StayTask->WakeRoutine(BehaviorTreeComponent);
                SetNPCState(ENPCStates::MoveToPoint);
            }
        }
    }
}
