// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Component/PlayerAttackComponent.h"
#include "Characters/Core/Component/CharacterStatComponent.h"

#include "Characters/Core/Interface/IDamageable.h"

#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

UPlayerAttackComponent::UPlayerAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	ComboAttackSections = { "Combo1", "Combo2", "Combo3" };

	CurrentComboIndex = 2;
	bIsMontageEnded = true;
	bNextCombo = true;
	bCanReceiveInput = false;
}

void UPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		StatComponent = OwnerCharacter->FindComponentByClass<UCharacterStatComponent>();
	}
}

void UPlayerAttackComponent::StartAttack()
{
	if (bCanReceiveInput)
	{
		bNextCombo = true;
	}

	if (bIsMontageEnded)
	{
		ProceedCombo();
	}
}

void UPlayerAttackComponent::ProceedCombo()
{
	if (!ComboAttackMontage || !AnimInstance)
		return;

	if (AnimInstance->Montage_IsPlaying(ComboAttackMontage))
		return;

	PlayComboAttackMontage(CurrentComboIndex);

	bNextCombo = false;		// 콤보 소비
	CurrentComboIndex++;	// 다음 콤보 인덱스
}

void UPlayerAttackComponent::PlayComboAttackMontage(int32 ComboIndex)
{
	if (!ComboAttackMontage || !AnimInstance)
		return;

	if (!ComboAttackSections.IsValidIndex(ComboIndex))
		return;

	AnimInstance->Montage_Play(ComboAttackMontage);
	AnimInstance->Montage_JumpToSection(ComboAttackSections[ComboIndex], ComboAttackMontage);

	bIsMontageEnded = false;
}

// AttackEndNotify에서 호출
void UPlayerAttackComponent::OnAttackEnded()
{
	if (bNextCombo == false || CurrentComboIndex == ComboAttackSections.Num())
	{
		// 1. 다음 콤보 입력이 없거나
		// 2. 콤보를 모두 수행했다면
		CurrentComboIndex = 0;	// 콤보 몽타주 인덱스 초기화
	}

	bIsMontageEnded = true;		// 애니메이션 몽타주 종료

	bCanReceiveInput = false;	// 따라서 콤보 입력 불가

	// 다음 콤보 입력이 있었다면 바로 다음 콤보로 진행
	// 콤보 이어서 실행
	if (bNextCombo)
	{
		ProceedCombo();
	}
}

// ReceiveInputNotify에서 호출
void UPlayerAttackComponent::ReceiveInput()
{
	bCanReceiveInput = true;
}

// AttackNotify
void UPlayerAttackComponent::OnAttack()
{
	if (!GetOwner())
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
	}
}
