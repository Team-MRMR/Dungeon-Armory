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

private:
    /** �����忡�� Enemy�� ���¸� �����ϴ� Ű */
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    FName EnemyState = "EnemyState";

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "AI")
    bool bDetectedTarget;

/***** Functions *****/
public:
    AEnemyAIController();

public:
    /** �������� EnemyState ���� ���� Getter, Setter */
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

    // ���� ó�� �Լ�
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

private:
	// AI ���¿� ���� �ൿ ó�� �Լ�
	void UpdateAIState();

};
