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

	// 소유 객체가 Pawn인지 확인
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;

	// AIController 가져오기
	AIController = Cast<AAIController>(OwnerPawn->GetController());
	if (AIController == nullptr)
		return;

	// 비헤이비어 트리 실행
	if (BehaviorTree && BehaviorTree->BlackboardAsset)
	{
		// 블랙보드 설정 (AIController에서 관리됨)
		AIController->UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

		// 블랙보드 변수 초기화
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsVector("HomeLocation", OwnerPawn->GetActorLocation());
			SetState(ENPCStates::Patrol);
		}

		// 비헤이비어 트리 실행 (이 시점에서 BehaviorTreeComponent가 자동으로 생성됨)
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
