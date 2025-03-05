// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AI/Team/TeamComponent.h"

#include "EnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EEnemyStates : uint8
{
	None	UMETA(DisplayName = "None"),

    Idle    UMETA(DisplayName = "Idle"),
    Patrol  UMETA(DisplayName = "Patrol"),
    Chase   UMETA(DisplayName = "Chase"),
    Return  UMETA(DisplayName = "Return")
};

// 전방 선언 (헤더 파일에서 포인터 변수만 선언할 경우)
class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class DUNGEON_ARMORY_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	

/***** Variables *****/
protected:
    // 기본 비헤이비어 트리 에셋
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTree;
    
    /** 비헤이비어 트리 컴포넌트 */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UBehaviorTreeComponent* BehaviorTreeComponent;

    /** 블랙보드 컴포넌트 */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UBlackboardComponent* BlackboardComponent;

    // AI 감지 시스템 (수정: AIController에서 관리)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI 시각 감지 설정
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

private:
    /** 블랙보드에서 Enemy의 상태를 저장하는 키 */
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    FName EnemyState = "EnemyState";

    // AI 시각 감지 설정
    UPROPERTY(VisibleAnywhere, Category = "AI")
    bool bDetectedTarget;

/***** Functions *****/
public:
    AEnemyAIController();

public:
    /** 블랙보드의 EnemyState 값에 대한 Getter, Setter */
    void SetEnemyState(EEnemyStates NewEnemyState);
	EEnemyStates GetEnemyState() const;

    /** Retrieved owner attitude toward given Other object */
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    /** Retrieve team identifier in form of FGenericTeamId */
    virtual FGenericTeamId GetGenericTeamId() const override;

    /** Assigns Team Agent to given TeamID */
    virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

protected:
    virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

    // 감지 처리 함수
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

private:
	// AI 상태에 따른 행동 처리 함수
	void UpdateAIState();

};
