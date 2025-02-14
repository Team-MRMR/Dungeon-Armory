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

    /** �����̺�� Ʈ�� ���� */
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    class UBehaviorTree* BehaviorTree;

    /** ������ ������Ʈ */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    class UBlackboardComponent* BlackboardComponent;

    /** �����̺�� Ʈ�� ������Ʈ */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    class UBehaviorTreeComponent* BehaviorTreeComponent;

/***** Functions *****/
public:
	AEnemyAIController();

public:
    /** ������ Ű ���� �Լ� */
    void SetBlackboardKey(FName KeyName, UObject* Value);

    /** ������ Ű ���� (Bool) */
    void SetBlackboardKeyBool(FName KeyName, bool bValue);

protected:
    virtual void OnPossess(APawn* InPawn) override;

};
