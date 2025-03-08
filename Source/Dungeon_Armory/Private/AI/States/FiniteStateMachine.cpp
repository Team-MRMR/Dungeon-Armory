// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/States/FiniteStateMachine.h"

// Sets default values for this component's properties
UFiniteStateMachine::UFiniteStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UFiniteStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!BlackboardComponent)
	{
		return;
	}

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
	//	// 적을 감지하지 못했으면 Return으로 변경
	//	SetNPCState(ENPCStates::Return);
	//	break;
	//case ENPCStates::Return:
	//	SetNPCState(ENPCStates::Patrol);
	//	//// 목표 지점에 도착했으면 Idle 상태로 변경
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

// Called when the game starts
void UFiniteStateMachine::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFiniteStateMachine::SetNPCState(ENPCStates NewNPCState)
{
	if (BlackboardComponent == nullptr)
	{
		return;
	}

	BlackboardComponent->SetValueAsEnum(NPCState, static_cast<uint8>(NewNPCState));
}

ENPCStates UFiniteStateMachine::GetNPCState() const
{
	if (BlackboardComponent == nullptr)
	{
		return ENPCStates::None;
	}

	int8 CurrNPCState = BlackboardComponent->GetValueAsEnum(NPCState);
	return static_cast<ENPCStates>(CurrNPCState);
}
