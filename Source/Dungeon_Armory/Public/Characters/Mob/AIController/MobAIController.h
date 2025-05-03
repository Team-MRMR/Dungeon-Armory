// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Core/AIControllerBase.h"
#include "Characters/Core/Component/CharacterStatComponent.h"

#include "MobAIController.generated.h"

class UCharacterStatComponent;
class UMovementControllerComponent;

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
	virtual void Tick(float DeltaTime) override;

/***** Stat *****/
private:
	UCharacterStatComponent* StatComponent;
	UMovementControllerComponent* MovementControllerComponent;

/***** Behavior Tree *****/
protected:
	// 블랙보드 키 이름 상수
	static const FName MobStateKey;

public:
	void SetMobState(EMobState NewState);

private:
	void InitializeBlackboardKeys();

	UFUNCTION()
	void OnMovementCompleted();

/***** AI *****/
protected:
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus) override;
};

// --- 블랙보드 키값 스트링 캐싱 ---
namespace BBKeys
{
	static const FName CurrentHealth(TEXT("CurrentHealth"));

	static const FName MobState(TEXT("MobState"));
	static const FName PatrolRadius(TEXT("PatrolRadius"));
	static const FName AcceptableRadius(TEXT("AcceptableRadius"));
}