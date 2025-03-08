// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/States/FiniteStateMachine.h"

#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionTypes.h"

// Sets default values for this component's properties
UFiniteStateMachine::UFiniteStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ENPCStates UFiniteStateMachine::GetState() const
{
	if (BlackboardComponent == nullptr)
	{
		return ENPCStates::None;
	}

	int8 CurrNPCState = BlackboardComponent->GetValueAsEnum(BBKey_NPCState);
	return static_cast<ENPCStates>(CurrNPCState);
}

void UFiniteStateMachine::SetState(ENPCStates NewNPCState)
{
	if (BlackboardComponent == nullptr)
	{
		return;
	}

	BlackboardComponent->SetValueAsEnum(BBKey_NPCState, static_cast<uint8>(NewNPCState));
}

void UFiniteStateMachine::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus) const
{
	if (BlackboardComponent == nullptr)
	{
		return;
	}
	bool bDetectedTarget = Stimulus.WasSuccessfullySensed();
	if (bDetectedTarget)
	{
		BlackboardComponent->SetValueAsObject("Target", Actor);
	}
	else
	{
		BlackboardComponent->SetValueAsObject("Target", nullptr);
	}
}

// Called when the game starts
void UFiniteStateMachine::BeginPlay()
{
	Super::BeginPlay();

	// ���� ��ü�� Pawn���� Ȯ��
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;

	// AIController ��������
	AIController = Cast<AAIController>(OwnerPawn->GetController());
	if (AIController == nullptr)
		return;

	// �����̺�� Ʈ�� ����
	if (BehaviorTree && BehaviorTree->BlackboardAsset)
	{
		// ������ ���� (AIController���� ������)
		AIController->UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

		// ������ ���� �ʱ�ȭ
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsVector("HomeLocation", OwnerPawn->GetActorLocation());
			SetState(ENPCStates::Patrol);
		}

		// �����̺�� Ʈ�� ���� (�� �������� BehaviorTreeComponent�� �ڵ����� ������)
		AIController->RunBehaviorTree(BehaviorTree);
	}
}

// Called every frame
void UFiniteStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BlackboardComponent == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("TickComponent of FSM"));

	//if (bDetectedTarget)
	//{
	//	if (GetNPCState() != ENPCStates::Chase)
	//	{
	//		SetNPCState(ENPCStates::Chase);
	//		return;
	//	}
	//}

	//ENPCStates State = GetNPCState();
	//switch (State)
	//{
	//case ENPCStates::Chase:
	//	// ���� �������� �������� Return���� ����
	//	SetNPCState(ENPCStates::Return);
	//	break;
	//case ENPCStates::Return:
	//	SetNPCState(ENPCStates::Patrol);
	//	//// ��ǥ ������ ���������� Idle ���·� ����
	//	//if (HasReachedHomePosition())
	//	//{
	//	//    SetNPCState(ENPCStates::Idle);
	//	//}
	//	break;
	//default:
	//	break;
	//}
}

void UFiniteStateMachine::ChangeState(IStatable* NextState)
{
	if (BlackboardComponent == nullptr)
	{
		return;
	}

	if (CurrState == nullptr || CurrState == NextState)
	{
		return;
	}

	CurrState->OnStateExit();
	CurrState = NextState;
	CurrState->OnStateEnter();
}

void UFiniteStateMachine::UpdateState()
{
	if (BlackboardComponent == nullptr)
	{
		return;
	}

	if (CurrState == nullptr)
	{
		return;
	}

	CurrState->OnStateUpdate();
}
