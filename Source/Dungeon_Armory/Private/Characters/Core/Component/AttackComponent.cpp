// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/Component/AttackComponent.h"
#include "Characters/Core/Component/CharacterStatComponent.h"

#include "Characters/Core/Interface/IDamageable.h"

#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	ComboAttackSections = { "Combo1", "Combo2", "Combo3" };

	bIsAttacking = false;
	bCanNextCombo = false;
	CurrentComboIndex = 0;
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		StatComponent = OwnerCharacter->FindComponentByClass<UCharacterStatComponent>();

		if (AnimInstance)
		{
			AnimInstance->OnMontageEnded.AddDynamic(this, &UAttackComponent::OnMontageEnded);
		}
	}
}

void UAttackComponent::StartAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("StartAttack"));
	if (bIsAttacking)
	{
		if (bCanNextCombo)
		{
			// 다음 콤보 진행
			ProceedCombo();
			bCanNextCombo = false;
		}
		return;
	}

	// 첫 공격
	CurrentComboIndex = 0;
	ProceedCombo();
}

void UAttackComponent::TryCombo()
{
	if (bCanNextCombo && bIsAttacking)
	{
		ProceedCombo();
		bCanNextCombo = false;
	}
}

void UAttackComponent::EnableCombo()
{
	bCanNextCombo = true;

	// 일정 시간 후 입력 허용 해제
	GetWorld()->GetTimerManager().SetTimer(
		ComboInputTimerHandle,
		this,
		&UAttackComponent::DisableComboInput,
		Duration,
		false
	);

	CurrentComboIndex++;
}

void UAttackComponent::DisableComboInput()
{
	bCanNextCombo = false;
}

void UAttackComponent::ProceedCombo()
{
	if (!ComboAttackMontage || ComboAttackSections.Num() == 0)
		return;

	if (!AnimInstance)
		return;

	if (AnimInstance->Montage_IsPlaying(ComboAttackMontage))
	{
		if (ComboAttackSections.IsValidIndex(CurrentComboIndex))
		{
			AnimInstance->Montage_JumpToSection(ComboAttackSections[CurrentComboIndex], ComboAttackMontage);
		}
	}
	else
	{
		PlayComboAttackMontage(CurrentComboIndex);
	}

	bIsAttacking = true;
	bCanNextCombo = false;
}

void UAttackComponent::PlayComboAttackMontage(int32 ComboIndex)
{
	if (!ComboAttackMontage || !AnimInstance || !ComboAttackSections.IsValidIndex(ComboIndex))
		return;

	AnimInstance->Montage_Play(ComboAttackMontage);
	AnimInstance->Montage_JumpToSection(ComboAttackSections[ComboIndex], ComboAttackMontage);
}

void UAttackComponent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;

	// 콤보 유지 불가
	bCanNextCombo = false;

	// 콤보 초기화
	CurrentComboIndex = 0;

	// 타이머 제거
	GetWorld()->GetTimerManager().ClearTimer(ComboInputTimerHandle);
}

void UAttackComponent::OnAttackHit()
{
	if (!GetOwner()) return;

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

	/*DrawDebugCapsule(
		GetWorld(),
		(Start + End) * 0.5f,
		TraceDistance * 0.5f,
		Radius,
		FRotationMatrix::MakeFromZ(End - Start).ToQuat(),
		TraceColor,
		false,
		1.0f
	);*/

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			/*DrawDebugSphere(
				GetWorld(),
				Hit.ImpactPoint,
				20.f,
				12,
				FColor::Red,
				false,
				1.0f
			);*/

			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Error, TEXT("Hit Actor: %s"), *HitActor->GetName());
				IIDamageable* DamagedActor = Cast<IIDamageable>(HitActor);
				if (DamagedActor && StatComponent)
				{
					const float DamageAmount = StatComponent->BaseDamage;
					DamagedActor->ReceiveDamage(DamageAmount);
				}
			}
		}
	}
}
