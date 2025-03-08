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

// ���� ���� (��� ���Ͽ��� ������ ������ ������ ���)
class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UFiniteStateMachine : public UActorComponent, public IStateMachine
{
	GENERATED_BODY()

/***** Variables *****/
protected:
	// �⺻ �����̺�� Ʈ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	/** �����̺�� Ʈ�� ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** ������ ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComponent;

private:
	/** �����忡�� NPC�� ���¸� �����ϴ� Ű */
	UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree", meta = (AllowPrivateAccess = "true"))
	FName NPCState = "NPCState";

	// AI ����
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
	/** �������� NPCState ���� ���� Getter, Setter */
	void SetNPCState(ENPCStates NewNPCState);
	ENPCStates GetNPCState() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
