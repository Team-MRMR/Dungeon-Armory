// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AI/Team/TeamComponent.h"
#include "AI/States/FiniteStateMachine.h"

#include "NPCAIController.generated.h"

UCLASS()
class DUNGEON_ARMORY_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	

/***** Variables *****/
protected:
    // AI 감지 시스템 (수정: AIController에서 관리)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI 시각 감지 설정
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

	// 팀 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Team")
	UTeamComponent* TeamComponent;

private:
    /** 블랙보드에서 NPC의 상태를 저장하는 키 */
    UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree")
    FName NPCState = "NPCState";

    // AI 시각 감지 설정
    UPROPERTY(VisibleAnywhere, Category = "BehaviorTree")
    bool bDetectedTarget;

    // AI 시각 감지 설정
    UPROPERTY(EditDefaultsOnly, Category = "Team")
	FGenericTeamId TeamId;

/***** Functions *****/
public:
    ANPCAIController();

    /** Retrieved owner attitude toward given Other object */
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    /** Retrieve team identifier in form of FGenericTeamId */
    virtual FGenericTeamId GetGenericTeamId() const override;

protected:
    virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
    // 감지 처리 함수
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

};
