// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Animation/AttackNotify.h"
#include "Characters/Core/Component/AttackComponent.h"

void UAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
		return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	if (UAttackComponent* AttackComponent = Owner->FindComponentByClass<UAttackComponent>())
	{
		AttackComponent->OnAttackHit(); // 컴포넌트 함수 호출

		// 다음 콤보 허용
		AttackComponent->EnableCombo();
	}
}
