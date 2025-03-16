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
            SetNPCState(ENPCStates::MoveToPoint);

            // �����̺�� Ʈ�� ���� (�� �������� BehaviorTreeComponent�� �ڵ����� ������)
            RunBehaviorTree(BehaviorTree);
        }
    }
}

/***** Derived Class *****/

void AStaticNPCAIController::OnTimeChanged()
{
    UE_LOG(LogTemp, Log, TEXT("Static NPC %s received time change event!"), *GetPawn()->GetName());

    if (Blackboard)
    {
        ENPCStates NewState = ENPCStates::MoveToPoint;
        Blackboard->SetValueAsEnum("NPCState", static_cast<uint8>(NewState));
        UE_LOG(LogTemp, Log, TEXT("Static NPC %s Blackboard State Changed to: %d"), *GetPawn()->GetName(), static_cast<uint8>(NewState));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Static NPC %s Blackboard is null!"), *GetPawn()->GetName());
    }

    SetNPCState(ENPCStates::MoveToPoint);
}
