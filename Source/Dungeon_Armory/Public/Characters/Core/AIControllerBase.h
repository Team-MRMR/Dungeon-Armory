// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "AIControllerBase.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UTeamComponent;
class UBehaviorTreeComponent;

/**
 * Base Class���� Controller�� ����� ������ �ð�,
 * Dervied Class������ �����̺�� Ʈ���� ���õ� �۾��� �����ϴ� ������ ����
 */
UCLASS()
class DUNGEON_ARMORY_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

/***** Unreal *****/
public:
	AAIControllerBase();

protected:
	virtual void BeginPlay() override;				// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;	// Called every frame
	virtual void OnPossess(APawn* InPawn) override;	// Called when the controller possess a Pawn

/***** AI *****/
protected:
    // AI ���� �ý���
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

protected:
	// ���� ó�� �Լ�
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

/***** Team *****/
protected:
	// �� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Team")
	UTeamComponent* TeamComponent;

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "Team")
	FGenericTeamId TeamId;

public:
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	
/***** Behavior Tree *****/
public:
	/** �����̺�� Ʈ�� ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** ������ ������Ʈ */
	UPROPERTY(VisibleAnywhere, Category = "Behavior Tree")
	UBlackboardComponent* BlackboardComponent;

protected:
	/** �����̺�� Ʈ�� */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	UBehaviorTree* BehaviorTree;

	/** �����忡�� NPC�� ���¸� �����ϴ� Ű */
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
	FName BBKey_NPCState = "NPCState";
};
