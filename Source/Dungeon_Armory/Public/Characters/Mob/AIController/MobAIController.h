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
	// ������ Ű �̸� ���
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

// --- ������ Ű�� ��Ʈ�� ĳ�� ---
namespace BBKeys
{
	// ���� ��ġ
	static const FName MobState(TEXT("MobState"));

	// �÷��̾� ��ü
	static const FName Target(TEXT("Target"));

	// ���� ���� ��ġ
	static const FName Stat(TEXT("Stat"));

	// �̵� ���� ��ü
	static const FName MovementController(TEXT("MovementController"));
	
	// �Ÿ� ���� ��ġ
	static const FName HomeLocation(TEXT("HomeLocation"));
	static const FName RandomLocation(TEXT("RandomLocation"));
}