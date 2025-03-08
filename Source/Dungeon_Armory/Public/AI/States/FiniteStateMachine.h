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

// ���� ���� (��� ���Ͽ��� ������ ������ ������ ���)
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
	/** AI ��Ʈ�ѷ� ���� */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	AAIController* AIController;

	/** �����̺�� Ʈ�� */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	/** �����̺�� Ʈ�� ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** ������ ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

private:
	/** �����忡�� NPC�� ���¸� �����ϴ� Ű */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	FName BBKey_NPCState = "NPCState";

	// AI ����
	IStatable* CurrState = nullptr;

/***** Functions *****/
public:	
	// Sets default values for this component's properties
	UFiniteStateMachine();

public:
	/** �������� NPCState ���� ���� Getter, Setter */
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
