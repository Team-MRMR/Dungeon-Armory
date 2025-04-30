// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "NPCAIController.generated.h"

UENUM(Blueprintable)
enum class ENPCStates : uint8
{
	None	UMETA(Hidden),

	Stay    UMETA(DisplayName = "Stay"),
	Wait	UMETA(DisplayName = "Wait"),
	Patrol  UMETA(DisplayName = "Patrol"),
	Chase   UMETA(DisplayName = "Chase"),
	Return  UMETA(DisplayName = "Return"),

	Size    UMETA(Hidden)
};

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UTeamComponent;
class UBehaviorTreeComponent;

UCLASS()
class DUNGEON_ARMORY_API ANPCAIController : public AAIController
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
protected:
	/** �����̺�� Ʈ�� */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	UBehaviorTree* BehaviorTree;

	/** �����̺�� Ʈ�� ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** ������ ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBlackboardComponent* BlackboardComponent;

	/** �����忡�� NPC�� ���¸� �����ϴ� Ű */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	FName BBKey_NPCState = "NPCState";

	// AI ����
	ENPCStates NPCState = ENPCStates::None;

/***** Functions (Unreal) *****/
public:
    ANPCAIController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

/***** Functions (AI) *****/
protected:
	virtual void OnPossess(APawn* InPawn) override;

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
