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
 * Base Class에서 Controller의 기능적 역할을 맡고,
 * Dervied Class에서는 비헤이비어 트리와 관련된 작업을 실행하는 역할을 수행
 */
UCLASS()
class DUNGEON_ARMORY_API ANPCAIControllerBase : public AAIController
{
	GENERATED_BODY()

/***** Variables (AI) *****/
protected:
    // AI 감지 시스템 (수정: AIController에서 관리)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI 시각 감지 설정
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

/***** Variables (Team) *****/
protected:
	// 팀 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Team")
	UTeamComponent* TeamComponent;

    // AI 시각 감지 설정
    UPROPERTY(VisibleAnywhere, Category = "Team")
	FGenericTeamId TeamId;
	
/***** Variables (Behavior Tree) *****/
public:
	/** 비헤이비어 트리 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** 블랙보드 컴포넌트 */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBlackboardComponent* BlackboardComponent;

protected:
	/** 비헤이비어 트리 */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	UBehaviorTree* BehaviorTree;

	/** 블랙보드에서 NPC의 상태를 저장하는 키 */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	FName BBKey_NPCState = "NPCState";

	// AI 상태
	ENPCStates NPCState = ENPCStates::None;

/***** Functions (Unreal) *****/
public:
	ANPCAIControllerBase();

protected:
	virtual void BeginPlay() override;				// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;	// Called every frame
	virtual void OnPossess(APawn* InPawn) override;	// Called when the controller possess a Pawn

/***** Functions (AI) *****/
    // 감지 처리 함수
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
