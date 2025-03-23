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
	/** AI가 머물러 있는 포인트 */
	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	AMovePoint* StayPoint;

	/** AI가 경로를 순회할 때 사용할 이동 타겟 포인트 */
	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	TArray<AMovePoint*> MovePoints;

	/** 현재 이동 지점 인덱스 */
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
