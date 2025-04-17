// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "NPCAIControllerBase.generated.h"

UENUM(Blueprintable)
enum class ENPCStates : uint8
{
	None	UMETA(Hidden),

	Stay			UMETA(DisplayName = "Stay"),			// Idle

	Wait			UMETA(DisplayName = "Wait"),			// Move
	MoveToPoint		UMETA(DisplayName = "MoveToPoint"),		// Move
	RoamToPoints	UMETA(DisplayName = "RoamToPoints"),	// Move
	Chase			UMETA(DisplayName = "Chase"),			// Move
	Return			UMETA(DisplayName = "Return"),			// Move

	Size    UMETA(Hidden)
};

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UTeamComponent;
class UBehaviorTreeComponent;


/**
 * Base Class���� Controller�� ����� ������ �ð�,
 * Dervied Class������ �����̺�� Ʈ���� ���õ� �۾��� �����ϴ� ������ ����
 */
UCLASS()
class DUNGEON_ARMORY_API ANPCAIControllerBase : public AAIController
{
	GENERATED_BODY()

/***** Variables (AI) *****/
protected:
    // AI ���� �ý��� (����: AIController���� ����)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

/***** Variables (Team) *****/
protected:
	// �� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Team")
	UTeamComponent* TeamComponent;

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "Team")
	FGenericTeamId TeamId;
	
/***** Variables (Behavior Tree) *****/
public:
	/** �����̺�� Ʈ�� ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** ������ ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBlackboardComponent* BlackboardComponent;

protected:
	/** �����̺�� Ʈ�� */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	UBehaviorTree* BehaviorTree;

	/** �����忡�� NPC�� ���¸� �����ϴ� Ű */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	FName BBKey_NPCState = "NPCState";

	// AI ����
	ENPCStates NPCState = ENPCStates::None;

/***** Functions (Unreal) *****/
public:
	ANPCAIControllerBase();

protected:
	virtual void BeginPlay() override;				// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;	// Called every frame
	virtual void OnPossess(APawn* InPawn) override;	// Called when the controller possess a Pawn

/***** Functions (AI) *****/
    // ���� ó�� �Լ�
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

/***** Functions (Team) *****/
public:
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
    virtual FGenericTeamId GetGenericTeamId() const override;

/***** Functions (Behavior Tree) *****/
public:
	ENPCStates GetNPCState() const;
	void SetNPCState(ENPCStates NewNPCState);

};
