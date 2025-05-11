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

	auto Player = Cast<AManny>(Owner);	// ���⼭ �÷��̾�� ���� ĳ���� ���� �ذ��ؾ� ��
	auto Mob = Cast<AMobBase>(Owner);	// ���⼭ �÷��̾�� ���� ĳ���� ���� �ذ��ؾ� ��
	if (!Mob && !Player)
		return;

	auto AttackComponent = Owner->FindComponentByClass<UAttackComponentBase>();
	if (!AttackComponent)
		return;

	AttackComponent->OnAttackEnd();
}
