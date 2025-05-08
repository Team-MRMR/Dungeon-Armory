// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Component/AttackComponentBase.h"
#include "Characters/Core/Component/CharacterStatComponent.h"

#include "Characters/Core/Interface/IDamageable.h"

#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

UAttackComponentBase::UAttackComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttackComponentBase::BeginPlay()
{
	Super::BeginPlay();

	auto OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		StatComponent = OwnerCharacter->FindComponentByClass<UCharacterStatComponent>();
	}
}

void UAttackComponentBase::StartAttack()
{
	
}

// AttackNotify
void UAttackComponentBase::OnAttack()
{
	/*if (!GetOwner())
		return;

	const FVector Start = GetOwner()->GetActorLocation();
	const FVector Forward = GetOwner()->GetActorForwardVector();
	const float TraceDistance = 150.f;
	const FVector End = Start + Forward * TraceDistance;

	const float Radius = 50.f;
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
		0.5f
	);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			DrawDebugSphere(
				GetWorld(),
				Hit.ImpactPoint,
				5.f,
				12,
				FColor::Red,
				false,
				0.5f
			);

			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Error, TEXT("Hit Actor: %s"), *HitActor->GetName());
				IIDamageable* DamagedActor = Cast<IIDamageable>(HitActor);
				if (DamagedActor && StatComponent)
				{
					const float DamageAmount = StatComponent->BaseAttackDamage;
					DamagedActor->ReceiveDamage(DamageAmount);
				}
			}
		}
	}*/
}
