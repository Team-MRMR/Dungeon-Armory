// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
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
    class UBehaviorTreeComponent* BehaviorTreeComponent;

    /** 블랙보드 컴포넌트 */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    class UBlackboardComponent* BlackboardComponent;

    // AI 감지 시스템 (수정: AIController에서 관리)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI 시각 감지 설정
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

/***** Functions *****/
public:
    AEnemyAIController();

public:
    /** 블랙보드 키 설정 함수 */
    void SetBlackboardKey(FName KeyName, UObject* Value);
    void SetBlackboardKeyBool(FName KeyName, bool bValue);

protected:
    virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

    // 감지 처리 함수
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

};
