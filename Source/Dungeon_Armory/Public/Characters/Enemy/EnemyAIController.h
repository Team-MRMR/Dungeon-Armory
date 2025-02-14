// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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
    virtual void BeginPlay() override;

    /** 비헤이비어 트리 참조 */
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    class UBehaviorTree* BehaviorTree;

    /** 블랙보드 컴포넌트 */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    class UBlackboardComponent* BlackboardComponent;

    /** 비헤이비어 트리 컴포넌트 */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    class UBehaviorTreeComponent* BehaviorTreeComponent;

/***** Functions *****/
public:
	AEnemyAIController();

public:
    /** 블랙보드 키 설정 함수 */
    void SetBlackboardKey(FName KeyName, UObject* Value);

    /** 블랙보드 키 설정 (Bool) */
    void SetBlackboardKeyBool(FName KeyName, bool bValue);

protected:
    virtual void OnPossess(APawn* InPawn) override;

};
