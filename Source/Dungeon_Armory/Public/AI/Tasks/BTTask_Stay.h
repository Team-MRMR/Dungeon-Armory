// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Stay.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API UBTTask_Stay : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

/***** Variables *****/
private:
	UBehaviorTreeComponent* BehaviorTreeCmp;
	
/***** Functions *****/
public:
	UBTTask_Stay();

protected:
    /** �½�ũ ���� */
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnTimeChanged();

};
