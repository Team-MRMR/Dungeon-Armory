// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Animation/AttackNotify.h"
#include "Characters/Core/Component/AttackComponentBase.h"

void UAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
		return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	if (UAttackComponentBase* PlayerAttackComponent = Owner->FindComponentByClass<UAttackComponentBase>())
	{
		PlayerAttackComponent->OnAttackHit(); // 컴포넌트 함수 호출
	}
}
