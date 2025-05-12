// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mannequin/Component/ToolComponent.h"
#include "Item/Interface/IToolType.h"

#include "GatherableActor/GatherableActorBase.h"

// Sets default values for this component's properties
UToolComponent::UToolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UToolComponent::BeginPlay()
{
	Super::BeginPlay();
	

	DoLineTrace(Hit);  // ���� Ʈ���̽� ����
}


// Called every frame
void UToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DoLineTrace(Hit);
}

void UToolComponent::PerformByResourceType()
{
    // 1. ���� Ʈ���̽��� ���� ������ ��� �˻�
    AActor* Target = Hit.GetActor();
    if (!Target)
        return;

    // 2. �÷��̾ ���� ���� �������� ToolType ��ȸ
	IIToolType* EquippedTool = Cast<IIToolType>(GetOwner());
	if (!EquippedTool)
		return;

    AGatherableActorBase* GatherableActor = Cast<AGatherableActorBase>(Target);
	if (!GatherableActor)
		return;

    // 3. ��� ���� �б� ó��
    EToolType ToolType = EquippedTool->Execute_GetToolType(GetOwner());  // �������Ʈ�� ���� �ʿ�
    EResourceType ResourceType = GatherableActor->GetResourceType();
    if (ToolType == EToolType::Axe && ResourceType == EResourceType::Tree)
    {
		UE_LOG(LogTemp, Warning, TEXT("PerformByResourceType() - Axe and Tree"));
    }
    else if(ToolType == EToolType::Pickaxe && ResourceType == EResourceType::Vein)
    {
        UE_LOG(LogTemp, Warning, TEXT("PerformByResourceType() - Pickaxe and Vein"));
    }
}

void UToolComponent::DoLineTrace(FHitResult& HitResult)
{
    // 1. �÷��̾� �Ǵ� ������Ʈ ���� ���
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
        return;

    // 2. ���� Ʈ���̽��� �������� ���� ���
    FVector Start = OwnerActor->GetActorLocation();
    FVector Forward = OwnerActor->GetActorForwardVector();
    float TraceDistance = 250.f; // ����/ä�� �Ÿ� (������ ���� ����)
    FVector End = Start + Forward * TraceDistance;

    // 3. �浹 �Ķ���� ����
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(OwnerActor); // �ڽ��� ����

    // 4. ���� ���� Ʈ���̽� ����
    GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility, // �Ǵ� Ŀ���� ä��: ECC_GameTraceChannel1 ��
        TraceParams
    );

    // 5. ����׿� �� �׸��� (�׽�Ʈ �ÿ���)
#if WITH_EDITOR
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.f, 0, 1.5f);
    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 12, FColor::Red, false, 0.f);
    }
#endif


    PerformByResourceType();
}

