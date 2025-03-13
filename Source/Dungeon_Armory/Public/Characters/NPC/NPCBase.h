// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "AI/Team/TeamComponent.h"

#include "NPCBase.generated.h"

class ANPCPatrolPoint;

UCLASS()
class DUNGEON_ARMORY_API ANPCBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()


/***** Variables (Team) *****/
public:	
	/** Team Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
	UTeamComponent* TeamComponent;

/***** Variables (Patrol) *****/
private:
	/** AI�� ��θ� ������ �� ����� �̵� Ÿ�� ����Ʈ */
	UPROPERTY(EditAnywhere, Category = "Patrol", meta = (AllowPrivateAccess = "true"))
	TArray<ANPCPatrolPoint*> PatrolPoints;

	/** ���� ��Ʈ�� ����Ʈ �ε��� */
	int32 CurrentPatrolIndex = 0;

/***** Functions (Unreal) *****/
public:
	ANPCBase();

protected:
	virtual void BeginPlay() override;

/***** Functions (Team) *****/
public:
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

/***** Functions (Patrol) *****/
public:
	UFUNCTION(BlueprintCallable, Category = "Patrol")
	FVector GetNextPatrolPoint();
};
