// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"

#include "NPCBase.generated.h"

class UTeamComponent;

class AMovePoint;

UCLASS()
class DUNGEON_ARMORY_API ANPCBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

/***** Variables (Team) *****/
public:	
	/** Team Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
	UTeamComponent* TeamComponent;

/***** Variables (Behavior Tree) *****/
private:
	/** AI�� �ӹ��� �ִ� ����Ʈ */
	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	AMovePoint* StayPoint;

	/** AI�� ��θ� ��ȸ�� �� ����� �̵� Ÿ�� ����Ʈ */
	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	TArray<AMovePoint*> MovePoints;

	/** ���� �̵� ���� �ε��� */
	int32 CurrMovepPointIndex = 0;


/***** Functions (Unreal) *****/
public:
	ANPCBase();

protected:
	virtual void BeginPlay() override;

/***** Function (Movement) *****/
public:
	void SetMovementSpeed(float NewSpeed);

/***** Functions (Team) *****/
public:
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

/***** Functions (Behavior Tree) *****/
public:
	FVector GetNextMovePoint();
	FVector GetStayPoint() const;
};
