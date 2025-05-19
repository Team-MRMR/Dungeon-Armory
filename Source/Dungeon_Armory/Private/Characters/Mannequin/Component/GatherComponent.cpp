// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mannequin/Component/GatherComponent.h"
#include "Characters/Core/Component/CharacterStatComponent.h"
#include "Characters/Mannequin/Interface/IToolEuipable.h"
#include "Characters/Mannequin/Manny.h"

#include "GatherableActor/GatherableActorBase.h"

// Sets default values for this component's properties
UGatherComponent::UGatherComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    bIsMontageEnded = true;
    bCanReceiveInput = true;
    bHasNextGather = false;
}

// Called when the game starts
void UGatherComponent::BeginPlay()
{
	Super::BeginPlay();
	
    OwnerPlayerCharacter = Cast<AManny>(GetOwner());
    if (OwnerPlayerCharacter)
    {
        AnimInstance = OwnerPlayerCharacter->GetMesh()->GetAnimInstance();
        Stat = OwnerPlayerCharacter->GetComponentByClass<UCharacterStatComponent>();
    }

}


// Called every frame
void UGatherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGatherComponent::StartGather()
{
    if (bCanReceiveInput)
    {
        bHasNextGather = true;
        bCanReceiveInput = false;
    }

    if (bIsMontageEnded)
    {
        ProceedGather();
    }
}

void UGatherComponent::OnGather()
{
    DoLineTrace(HitResult);

    // 1. ���� Ʈ���̽��� ���� ������ ��� �˻�
    AActor* Target = HitResult.GetActor();
    if (!Target)
        return;

    // 2. �÷��̾��� ������ �ڿ� ������ Ÿ���� �������� ���� �غ�
    IIToolEuipable* IToolEuipable = Cast<IIToolEuipable>(GetOwner());
	if (!IToolEuipable)
		return;

    AGatherableActorBase* GatherableActor = Cast<AGatherableActorBase>(Target);
	if (!GatherableActor)
		return;

    // 3. ��� ���� �б� ó��
	EResourceType ResourceType = GatherableActor->GetResourceType();      // �ڿ� ���Ϳ��� ResourceType�� ������
    if (ToolType == EToolType::Axe && ResourceType == EResourceType::Tree)
    {
        Logging();
    }
    else if(ToolType == EToolType::Pickaxe && ResourceType == EResourceType::Vein)
    {
        Mining();
    }
}

void UGatherComponent::OnGatherEnd()
{
    bIsMontageEnded = true;
    bCanReceiveInput = true;

    if (bHasNextGather)
    {
        ProceedGather();
        bHasNextGather = false;
    }
}

void UGatherComponent::ReceiveInput()
{
    bCanReceiveInput = true;
}

void UGatherComponent::DoLineTrace(FHitResult& OutHitResult)
{
    // 1. �÷��̾� �Ǵ� ������Ʈ ���� ���
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
        return;

    // 2. ���� Ʈ���̽��� �������� ���� ���
    FVector Start, End;
    FRotator ViewRot;
    OwnerActor->GetActorEyesViewPoint(Start, ViewRot);
    End = Start + ViewRot.Vector() * GatheringDistance;

    // 3. �浹 �Ķ���� ����
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(OwnerActor); // �ڽ��� ����

    // 4. ���� ���� Ʈ���̽� ����
    bIsHit = GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        Start,
        End,
        ECC_Visibility, // �Ǵ� Ŀ���� ä��: ECC_GameTraceChannel1 ��
        TraceParams
    );

    // 5. ����׿� �� �׸��� (�׽�Ʈ �ÿ���)
#if WITH_EDITOR
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f);
    if (OutHitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), OutHitResult.ImpactPoint, 5.0f, 12, FColor::Red, false, 0.1f);
    }
#endif
}

void UGatherComponent::UpdateToolType()
{
    auto OwnerActor = GetOwner();
    if (!OwnerActor)
        return;

    auto IToolEuipable = Cast<IIToolEuipable>(OwnerActor);
    if (!IToolEuipable)
        return;

    ToolType = IToolEuipable->Execute_GetToolType(OwnerActor);
}

void UGatherComponent::Logging()
{
    if (bIsHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (!HitActor)
            return;

        auto GatherableActor = Cast<AGatherableActorBase>(HitActor);
        if (GatherableActor)
        {
            IIDamageable* DamagedActor = Cast<IIDamageable>(GatherableActor);
            if (DamagedActor && Stat)
            {
                const float DamageAmount = Stat->BaseAttackDamage;
                DamagedActor->ReceiveDamage(DamageAmount);

                const float ConsumptionStamina = Stat->Stamina.LoggingConsumption;
                Stat->ConsumeStamina(ConsumptionStamina); // ���¹̳� �Һ�

                OwnerPlayerCharacter->DecreaseDurability();  // ���� ������ ����

                PlayGatherMontage();

                return;
            }
        }
    }
}

void UGatherComponent::Mining()
{
    if (bIsHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (!HitActor)
            return;

        auto GatherableActor = Cast<AGatherableActorBase>(HitActor);
        if (GatherableActor)
        {
            IIDamageable* DamagedActor = Cast<IIDamageable>(GatherableActor);
            if (DamagedActor && Stat)
            {
                const float DamageAmount = Stat->BaseAttackDamage;
                DamagedActor->ReceiveDamage(DamageAmount);

                const float ConsumptionStamina = Stat->Stamina.MiningConsumption;
                Stat->ConsumeStamina(ConsumptionStamina); // ���¹̳� �Һ�

                OwnerPlayerCharacter->DecreaseDurability();  // ���� ������ ����

                return;
            }
        }
    }
}

void UGatherComponent::ProceedGather()
{
    UpdateToolType();

    PlayGatherMontage();

    bHasNextGather = false;
}

void UGatherComponent::PlayGatherMontage()
{
    if (!AnimInstance)
        return;

    if (!LoggingMontage || !MiningMontage)
        return;

    if (AnimInstance->Montage_IsPlaying(LoggingMontage) || AnimInstance->Montage_IsPlaying(MiningMontage))
        return;

    if (ToolType == EToolType::Axe)
    {
        const float ConsumptionStamina = Stat->Stamina.LoggingConsumption;
        const float CurrentStamina = Stat->Stamina.GetCurrent();

        // ���� ���¹̳ʰ� �Һ� ���¹̳ʺ��� ������ ������ �� ����
        if (CurrentStamina <= ConsumptionStamina)
            return;

        AnimInstance->Montage_Play(LoggingMontage);
    }
    else if (ToolType == EToolType::Pickaxe)
    {
        const float ConsumptionStamina = Stat->Stamina.MiningConsumption;
        const float CurrentStamina = Stat->Stamina.GetCurrent();

        // ���� ���¹̳ʰ� �Һ� ���¹̳ʺ��� ������ ������ �� ����
        if (CurrentStamina <= ConsumptionStamina)
            return;
        AnimInstance->Montage_Play(MiningMontage);
    }
    
    bIsMontageEnded = false;
}
