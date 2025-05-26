// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/Tasks/BTTask_Die.h"

UBTTask_Die::UBTTask_Die()
{
	bNotifyTick = false;
	NodeName = TEXT("Mob Die");
}

EBTNodeResult::Type UBTTask_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}