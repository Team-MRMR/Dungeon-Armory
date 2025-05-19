// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/AI/NPCAIController.h"
#include "Characters/NPC/NPCBase.h"

#include "Characters/Core/AI/Interface/IMovableTask.h"
#include "Characters/Core/Component/CharacterStatComponent.h"
#include "Characters/Core/Component/MovementControllerComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Navigation/PathFollowingComponent.h"

ANPCAIController::ANPCAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ANPCAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // ������Ʈ ���� �Ҵ�
    if (ACharacter* NPCCharacter = Cast<ANPCBase>(InPawn))
    {
        if (ANPCBase* NPCBase = Cast<ANPCBase>(NPCCharacter))
        {
			Stat = NPCBase->FindComponentByClass<UCharacterStatComponent>();

            MovementController = NPCBase->FindComponentByClass<UMovementControllerComponent>();
            //MovementController->OnMovementCompleted.AddDynamic(this, &ANPCAIController::OnMovementCompleted);
        }
    }

    // �����̺�� Ʈ�� ����
    if (BehaviorTree && BehaviorTree->BlackboardAsset)
    {
        // ������ ���� (AIController���� ������)
        UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

        // ������ ���� �ʱ�ȭ
        if (BlackboardComponent)
        {
            InitializeBlackboardKeys();
        }

        // �����̺�� Ʈ�� ���� (�� �������� BehaviorTreeComponent�� �ڵ����� ������)
        RunBehaviorTree(BehaviorTree);

        // ���������� ������ BehaviorTreeComponent�� �����ͼ� ��� ������ �Ҵ�
        BehaviorTreeComponent = FindComponentByClass<UBehaviorTreeComponent>();
    }
}

void ANPCAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANPCAIController::SetNPCState(ENPCStates NewNPCState)
{
    if (BlackboardComponent == nullptr)
    {
        return;
    }

    BlackboardComponent->SetValueAsEnum(BBKey_NPCState, static_cast<uint8>(NewNPCState));
}

void ANPCAIController::InitializeBlackboardKeys()
{
    // --- ���� ���� Ű�� ---
    BlackboardComponent->SetValueAsEnum(NPCBBKeys::NPCState, static_cast<uint8>(ENPCStates::Stay));

    // --- ������Ʈ ���� Ű�� ---
    BlackboardComponent->SetValueAsObject(NPCBBKeys::Stat, Stat);
    BlackboardComponent->SetValueAsObject(NPCBBKeys::MovementController, MovementController);

    // --- �Ÿ� ���� Ű�� ---
    BlackboardComponent->SetValueAsVector(NPCBBKeys::HomeLocation, GetPawn()->GetActorLocation());
}

void ANPCAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    if (!BehaviorTreeComponent)
        return;

    const UBTNode* ActiveNode = BehaviorTreeComponent->GetActiveNode();
    if (ActiveNode)
    {
        // IIMovableTask �������̽��� ����Ͽ� �̵� �Ϸ� ó��
        IIMovableTask* MovableTask = const_cast<IIMovableTask*>(Cast<IIMovableTask>(ActiveNode));
        if (MovableTask)
        {
            if (Result == EPathFollowingResult::Success)
            {
                MovableTask->OnMoveCompleted(BehaviorTreeComponent);    // �̵� �Ϸ� ó���� ��� �ұ�. Result.Code�� �Ϸ�� ���п� ���� ������ �ؾ� ��
            }
            else
            {
                MovableTask->OnMoveCompleted(BehaviorTreeComponent);
                BehaviorTreeComponent->RestartTree();
            }
        }
    }
}