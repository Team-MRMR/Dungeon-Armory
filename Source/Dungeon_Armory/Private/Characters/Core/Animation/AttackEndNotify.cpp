// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Animation/AttackEndNotify.h"
#include "Characters/Core/Component/AttackComponentBase.h"

#include "Characters/Mob/MobBase.h"
#include "Characters/Mannequin/Manny.h"

void UAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
		return;

	auto Player = Cast<AManny>(Owner);	// 여기서 플레이어랑 몬스터 캐스팅 문제 해결해야 함
	auto Mob = Cast<AMobBase>(Owner);	// 여기서 플레이어랑 몬스터 캐스팅 문제 해결해야 함
	if (!Mob && !Player)
		return;

	auto AttackComponent = Owner->FindComponentByClass<UAttackComponentBase>();
	if (!AttackComponent)
		return;

	AttackComponent->OnAttackEnd();
}
