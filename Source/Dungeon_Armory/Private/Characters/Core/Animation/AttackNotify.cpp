// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Animation/AttackNotify.h"
#include "Characters/Core/Component/AttackComponentBase.h"

#include "Characters/Mob/MobBase.h"
#include "Characters/Mannequin/Manny.h"
#include "Characters/Mannequin/Interface/IToolEuipable.h"
#include "Characters/Mannequin/Component/GatherComponent.h"

void UAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
		return;

	auto IToolEuipable = Cast<IIToolEuipable>(Owner);
	if (IToolEuipable)
	{
		auto Player = Cast<AManny>(Owner);
		if (!Player)
			return;

		EToolType ToolType = IToolEuipable->Execute_GetToolType(Owner);
		if (ToolType == EToolType::Weapon)
		{
			auto AttackComponent = Player->FindComponentByClass<UAttackComponentBase>();
			if (!AttackComponent)
				return;

			AttackComponent->OnAttack();
		}
		else if (ToolType == EToolType::Axe)
		{
			auto GatherComponent = Player->FindComponentByClass<UGatherComponent>();
			if (!GatherComponent)
				return;

			GatherComponent->OnGather();
		}
		else if (ToolType == EToolType::Pickaxe)
		{
			auto GatherComponent = Player->FindComponentByClass<UGatherComponent>();
			if (!GatherComponent)
				return;

			GatherComponent->OnGather(); // 여기서 채집을 해야 하는데 힛 리줄트 문제 해결해야 함
		}

		return;
	}

	
	auto Mob = Cast<AMobBase>(Owner);
	if (Mob)
	{
		auto AttackComponent = Owner->FindComponentByClass<UAttackComponentBase>();
		if (!AttackComponent)
			return;

		AttackComponent->OnAttack();

		return;
	}
}
