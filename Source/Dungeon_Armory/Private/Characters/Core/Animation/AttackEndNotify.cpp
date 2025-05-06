// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Animation/AttackEndNotify.h"
#include "Characters/Core/Component/AttackComponentBase.h"

void UAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
		return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
		return;

	if (UAttackComponentBase* PlayerAttackComponent = Owner->FindComponentByClass<UAttackComponentBase>())
	{
		PlayerAttackComponent->OnAttackEnded();
	}
}
