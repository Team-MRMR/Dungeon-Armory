// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "EnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EEnemyStates : uint8
{
    Idle    UMETA(DisplayName = "Idle"),
    Patrol  UMETA(DisplayName = "Patrol"),
    Chase   UMETA(DisplayName = "Chase"),
    Return  UMETA(DisplayName = "Return")
};

// ���� ���� (��� ���Ͽ��� ������ ������ ������ ���)
class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;

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
    UBehaviorTreeComponent* BehaviorTreeComponent;

    /** ������ ������Ʈ */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UBlackboardComponent* BlackboardComponent;

    // AI ���� �ý��� (����: AIController���� ����)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

    /** �����忡�� Enemy�� ���¸� �����ϴ� Ű */
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    FName BlackboardKey_EnemyState = "EnemyState";

/***** Functions *****/
public:
    AEnemyAIController();

public:
    /** �����忡 EnemyState ���� �����ϴ� �Լ� */
    void SetEnemyState(EEnemyStates NewState);

protected:
    virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

    // ���� ó�� �Լ�
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

};
