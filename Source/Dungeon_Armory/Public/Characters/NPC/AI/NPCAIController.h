// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Core/AI/AIControllerBase.h"

#include "NPCAIController.generated.h"

UENUM(Blueprintable)
enum class ENPCStates : uint8
{
	None	UMETA(Hidden),

	Stay			UMETA(DisplayName = "Stay"),			// Idle

	Wait			UMETA(DisplayName = "Wait"),			// Move
	MoveToPoint		UMETA(DisplayName = "MoveToPoint"),		// Move
	RoamToPoints	UMETA(DisplayName = "RoamToPoints"),	// Move
	Return			UMETA(DisplayName = "Return"),			// Move

	Size    UMETA(Hidden)
};


class UCharacterStatComponent;
class UMovementControllerComponent;

UCLASS()
class DUNGEON_ARMORY_API ANPCAIController : public AAIControllerBase
{
	GENERATED_BODY()

/***** Functions (Unreal) *****/
public:
	ANPCAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;


/***** Component *****/
private:
	UCharacterStatComponent* Stat;
	UMovementControllerComponent* MovementController;

/***** Functions (Task) *****/
public:
	void SetNPCState(ENPCStates NewNPCState);

private:
	void InitializeBlackboardKeys();
	void OnMovementCompleted();
};

namespace NPCBBKeys
{
	// ���� ��ġ
	static const FName NPCState(TEXT("NPCState"));

	// �÷��̾� ��ü
	static const FName Target(TEXT("Target"));

	// ���� ���� ��ġ
	static const FName Stat(TEXT("Stat"));

	// �̵� ���� ��ü
	static const FName MovementController(TEXT("MovementController"));

	// �Ÿ� ���� ��ġ
	static const FName HomeLocation(TEXT("HomeLocation"));
	//static const FName RandomLocation(TEXT("RandomLocation"));
}