// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mob/Tasks/BTTask_Attack.h"

#include "Characters/Mob/MobBase.h"
#include "Characters/Mob/AIController/MobAIController.h"
#include "Characters/Mob/Component/MobAttackComponent.h"

#include "Characters/Core/Component/CharacterStatComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	NodeName = TEXT("Mob Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto Controller = OwnerComp.GetAIOwner();
    if(!Controller)
		return EBTNodeResult::Failed;

	auto Mob = Cast<AMobBase>(Controller->GetPawn());
	if (!Mob)
		return EBTNodeResult::Failed;

	auto AttackComponent = Mob->AttackComponent;
	if (!AttackComponent)
		return EBTNodeResult::Failed;

	AttackComponent->StartAttack();

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
		return;

	auto AttackComponent = Cast<UMobAttackComponent>(Blackboard->GetValueAsObject(TEXT("AttackComponent")));
	if (AttackComponent->GetCanAttack())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
