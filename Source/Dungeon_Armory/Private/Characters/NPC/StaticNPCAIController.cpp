// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/StaticNPCAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Manager/InGameTimeManager.h"

/***** Base Class *****/

void AStaticNPCAIController::BeginPlay()
{
	Super::BeginPlay();

    // ���� �ð� �Ŵ��� ã��
    UInGameTimeManager* TimeManager = UInGameTimeManager::GetInstance();
    if (TimeManager)
    {
        TimeManager->OnTimeChanged.AddDynamic(this, &AStaticNPCAIController::OnTimeChanged);
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
        }
    }
}

/***** Derived Class *****/

void AStaticNPCAIController::OnTimeChanged()
{
    SetNPCState(ENPCStates::MoveToPoint);
}
