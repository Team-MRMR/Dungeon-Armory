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
		// 애님 인스턴스 생성
		AnimInstance = Mob->GetMesh()->GetAnimInstance();
		if (!AnimInstance)
			return;

		// 스탯 컴포넌트 생성
		Stat = Mob->StatComponent;
		if (!Stat)
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
	if (RandomValue <= Stat->CriticalChance)
	{
		// 크리티컬 공격
		AnimInstance->Montage_Play(CriticalAttackMontage);
	}
	else
	{
		// 일반 공격
		AnimInstance->Montage_Play(NormalAttackMontage);
	}
}

void UMobAttackComponent::OnAttack()
{
	if (!GetOwner())
		return;

	const FVector Start = GetOwner()->GetActorLocation();
	const FVector Forward = GetOwner()->GetActorForwardVector();
	const float TraceDistance = Stat->AttackRange;
	const FVector End = Start + Forward * TraceDistance;

	const float Radius = Stat->AttackRadius;
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(Radius),
		Params
	);

	FColor TraceColor = bHit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(
		GetWorld(),
		(Start + End) * 0.5f,
		TraceDistance * 0.5f,
		Radius,
		FRotationMatrix::MakeFromZ(End - Start).ToQuat(),
		TraceColor,
		false,
		0.25f
	);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			DrawDebugSphere(
				GetWorld(),
				Hit.ImpactPoint,
				1.0f,
				12,
				FColor::Red,
				false,
				0.25f
			);

			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Error, TEXT("Hit Actor: %s"), *HitActor->GetName());
				IIDamageable* DamagedActor = Cast<IIDamageable>(HitActor);
				if (DamagedActor && Stat)
				{
					const float DamageAmount = Stat->BaseAttackDamage;
					DamagedActor->ReceiveDamage(DamageAmount);
				}
			}
		}
	}
}

