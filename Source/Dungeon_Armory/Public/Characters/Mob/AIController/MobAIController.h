// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Core/AI/AIControllerBase.h"
#include "Characters/Core/Component/CharacterStatComponent.h"

#include "MobAIController.generated.h"

class UCharacterStatComponent;
class UMovementControllerComponent;
class UMobAttackComponent;

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

/***** Component *****/
private:
	UCharacterStatComponent* StatComponent;
	UMovementControllerComponent* MovementControllerComponent;
	UMobAttackComponent* MobAttackComponent;

/***** Behavior Tree *****/
protected:
	// ������ Ű �̸� ���
	static const FName MobStateKey;

public:
	void SetMobState(EMobState NewState);

private:
	void InitializeBlackboardKeys();
	void OnMovementCompleted();

/***** AI *****/
protected:
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus) override;
};

// --- ������ Ű�� ��Ʈ�� ĳ�� ---
namespace MobBBKeys
{
	// ���� ��ġ
	static const FName MobState(TEXT("MobState"));

	// �÷��̾� ��ü
	static const FName Target(TEXT("Target"));

	// ���� ���� ��ġ
	static const FName Stat(TEXT("Stat"));

	// �̵� ���� ��ü
	static const FName MovementController(TEXT("MovementController"));

	// ���� ���� ��ü
	static const FName AttackComponent(TEXT("AttackComponent"));

	// �Ÿ� ���� ��ġ
	static const FName HomeLocation(TEXT("HomeLocation"));
	static const FName RandomLocation(TEXT("RandomLocation"));
}