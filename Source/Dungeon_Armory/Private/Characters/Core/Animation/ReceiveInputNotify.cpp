// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Animation/ReceiveInputNotify.h"
#include "Characters/Mannequin/Component/PlayerAttackComponent.h"

void UReceiveInputNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
		return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
		return;

	if (UPlayerAttackComponent* PlayerAttackComponent = Owner->FindComponentByClass<UPlayerAttackComponent>())
	{
		PlayerAttackComponent->ReceiveInput();
	}
}
