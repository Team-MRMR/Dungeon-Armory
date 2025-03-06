// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AI/Team/TeamComponent.h"

#include "NPCAIController.generated.h"

UENUM(BlueprintType)
enum class ENPCStates : uint8
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
class DUNGEON_ARMORY_API ANPCAIController : public AAIController
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

	// �� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Team")
	UTeamComponent* TeamComponent;

private:
    /** �����忡�� NPC�� ���¸� �����ϴ� Ű */
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    FName NPCState = "NPCState";

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "AI")
    bool bDetectedTarget;

    // AI �ð� ���� ����
    UPROPERTY(EditDefaultsOnly, Category = "Team")
	FGenericTeamId TeamId;

/***** Functions *****/
public:
    ANPCAIController();

    /** Retrieved owner attitude toward given Other object */
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    /** Retrieve team identifier in form of FGenericTeamId */
    virtual FGenericTeamId GetGenericTeamId() const override;

public:
    /** �������� NPCState ���� ���� Getter, Setter */
    void SetNPCState(ENPCStates NewNPCState);
	ENPCStates GetNPCState() const;

protected:
    virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
    // ���� ó�� �Լ�
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

private:
	// AI ���¿� ���� �ൿ ó�� �Լ�
	void UpdateAIState();

};
