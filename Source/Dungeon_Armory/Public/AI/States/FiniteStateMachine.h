// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/States/IStateMachine.h"

#include "FiniteStateMachine.generated.h"

UENUM(BlueprintType)
enum class ENPCStates : uint8
{
	None	UMETA(Hidden),

	Idle    UMETA(DisplayName = "Idle"),
	Patrol  UMETA(DisplayName = "Patrol"),
	Chase   UMETA(DisplayName = "Chase"),
	Return  UMETA(DisplayName = "Return")
};

// 전방 선언 (헤더 파일에서 포인터 변수만 선언할 경우)
class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UFiniteStateMachine : public UActorComponent, public IStateMachine
{
	GENERATED_BODY()

/***** Variables *****/
protected:
	// 기본 비헤이비어 트리 에셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	/** 비헤이비어 트리 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** 블랙보드 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComponent;

private:
	/** 블랙보드에서 NPC의 상태를 저장하는 키 */
	UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	FName NPCState = "NPCState";

	// AI 상태
	IStatable* CurrState;

/***** Functions *****/
public:	
	// Sets default values for this component's properties
	UFiniteStateMachine();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ChangeState(IStatable* Nexttate) override;

	virtual void UpdateState() override;

public:
	/** 블랙보드의 NPCState 값에 대한 Getter, Setter */
	void SetNPCState(ENPCStates NewNPCState);
	ENPCStates GetNPCState() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
