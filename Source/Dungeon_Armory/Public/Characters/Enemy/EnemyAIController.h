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
    // �⺻ �����̺�� Ʈ�� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTree;
    
    /** �����̺�� Ʈ�� ������Ʈ */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    class UBehaviorTreeComponent* BehaviorTreeComponent;

    /** ������ ������Ʈ */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    class UBlackboardComponent* BlackboardComponent;

    // AI ���� �ý��� (����: AIController���� ����)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

/***** Functions *****/
public:
    AEnemyAIController();

public:
    /** ������ Ű ���� �Լ� */
    void SetBlackboardKey(FName KeyName, UObject* Value);
    void SetBlackboardKeyBool(FName KeyName, bool bValue);

protected:
    virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

    // ���� ó�� �Լ�
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

};
