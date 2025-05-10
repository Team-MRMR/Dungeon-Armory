// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Core/Component/MobAttackComponent.h"

#include "Characters/Mob/MobBase.h"
#include "Characters/Core/Component/CharacterStatComponent.h"

// Sets default values for this component's properties
UMobAttackComponent::UMobAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UMobAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Mob = Cast<AMobBase>(GetOwner());
	if (Mob)
	{
		// �ִ� �ν��Ͻ� ����
		AnimInstance = Mob->GetMesh()->GetAnimInstance();
		if (!AnimInstance)
			return;

		// ���� ������Ʈ ����
		StatComponent = Mob->StatComponent;
		if (!StatComponent)
			return;
	}
}

// Called every frame
void UMobAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMobAttackComponent::StartAttack()
{
	if (!AnimInstance)
		return;

	if (!NormalAttackMontage || !CriticalAttackMontage)
		return;

	const float RandomValue = FMath::FRandRange(0.0f, 1.0f);
	if (RandomValue <= StatComponent->CriticalChance)
	{
		// ũ��Ƽ�� ����
		AnimInstance->Montage_Play(CriticalAttackMontage);
	}
	else
	{
		// �Ϲ� ����
		AnimInstance->Montage_Play(NormalAttackMontage);
	}
}

