// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Core/AIControllerBase.h"

#include "Characters/Core/CharacterStatComponent.h"

#include "MobAIController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API AMobAIController : public AAIControllerBase
{
	GENERATED_BODY()
	
/***** Unreal *****/
public:
	AMobAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

/***** Stat *****/
private:
	UCharacterStatComponent* StatComponent;

/***** Behavior Tree *****/
protected:
	// 블랙보드 키 이름 상수
	static const FName MobStateKey;

public:
	void SetMobState(EMobState NewState);

private:
	void InitializeBlackboardKeys();

	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

/***** AI *****/
protected:
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus) override;
};
