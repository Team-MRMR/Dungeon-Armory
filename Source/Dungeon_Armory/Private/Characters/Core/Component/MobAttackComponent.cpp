// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Core/Component/MobAttackComponent.h"
#include "Characters/Core/Component/CharacterStatComponent.h"
#include "Characters/Core/Animation/AttackNotify.h"
#include "Characters/Core/Animation/AttackEndNotify.h"

#include "Characters/Mob/MobBase.h"


// Sets default values for this component's properties
UMobAttackComponent::UMobAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bIsStartedAttack = false;
	bIsEndedAttack = false;
	bCanAttack = true;
}

// Called when the game starts
void UMobAttackComponent::BeginPlay()
{
	// 애님 인스턴스 생성
	// 스탯 컴포넌트 생성
	Super::BeginPlay();
}

// Called every frame
void UMobAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsStartedAttack)
	{
		ElapsedTime += DeltaTime;
		if (bIsEndedAttack && ElapsedTime >= Stat->GetAttackCooldown())
		{
			bIsStartedAttack = false;
			bCanAttack = true;
		}
	}
}

void UMobAttackComponent::StartAttack()
{
	if (!AnimInstance)
		return;

	if (!NormalAttackMontage || !CriticalAttackMontage)
		return;

	//const float RandomValue = FMath::FRandRange(0.0f, 1.0f);
	//if (RandomValue <= Stat->CriticalChance)
	//{
	//	const float AttackRate = Stat->GetAttackPlayRate(NormalAttackMontage->GetPlayLength());
	//	AnimInstance->Montage_Play(NormalAttackMontage);	// 일반 공격
	//}
	//else
	//{
	//	const float AttackRate = Stat->GetAttackPlayRate(CriticalAttackMontage->GetPlayLength());
	//	AnimInstance->Montage_Play(CriticalAttackMontage);	// 크리티컬 공격
	//}

	const float AttackRate = Stat->GetAttackPlayRate(NormalAttackMontage->GetPlayLength());
	AnimInstance->Montage_Play(NormalAttackMontage, AttackRate, EMontagePlayReturnType::MontageLength, 0.0f, true);	// 일반 공격

	ElapsedTime = 0.0f;
	bIsStartedAttack = true;
	bIsEndedAttack = false;

	bCanAttack = false;
}

bool UMobAttackComponent::GetCanAttack() const
{
	return bCanAttack;
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

void UMobAttackComponent::OnAttackEnd()
{
	bIsEndedAttack = true;
}

