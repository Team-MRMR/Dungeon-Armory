// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

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
class AAIController;
class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;
struct FAIStimulus;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UFiniteStateMachine : public UActorComponent, public IStateMachine
{
	GENERATED_BODY()

/***** Variables *****/
public:
	/** AI 컨트롤러 참조 */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	AAIController* AIController;

	/** 비헤이비어 트리 */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	/** 비헤이비어 트리 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** 블랙보드 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

private:
	/** 블랙보드에서 NPC의 상태를 저장하는 키 */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	FName BBKey_NPCState = "NPCState";

	// AI 상태
	IStatable* CurrState = nullptr;

/***** Functions *****/
public:	
	// Sets default values for this component's properties
	UFiniteStateMachine();

public:
	/** 블랙보드의 NPCState 값에 대한 Getter, Setter */
	ENPCStates GetState() const;
	void SetState(ENPCStates NewNPCState);

	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ChangeState(IStatable* NextState) override;

	virtual void UpdateState() override;

};
