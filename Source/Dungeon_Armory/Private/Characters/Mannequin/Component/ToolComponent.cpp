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
	

	DoLineTrace(Hit);  // 라인 트레이스 수행
}


// Called every frame
void UToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DoLineTrace(Hit);
}

void UToolComponent::PerformByResourceType()
{
    // 1. 라인 트레이스를 통해 감지한 대상 검사
    AActor* Target = Hit.GetActor();
    if (!Target)
        return;

    // 2. 플레이어가 현재 장착 아이템의 ToolType 조회
	IIToolType* EquippedTool = Cast<IIToolType>(GetOwner());
	if (!EquippedTool)
		return;

    AGatherableActorBase* GatherableActor = Cast<AGatherableActorBase>(Target);
	if (!GatherableActor)
		return;

    // 3. 대상에 따라 분기 처리
    EToolType ToolType = EquippedTool->Execute_GetToolType(GetOwner());  // 블루프린트와 연동 필요
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
    // 1. 플레이어 또는 컴포넌트 오너 얻기
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
        return;

    // 2. 라인 트레이스의 시작점과 끝점 계산
    FVector Start = OwnerActor->GetActorLocation();
    FVector Forward = OwnerActor->GetActorForwardVector();
    float TraceDistance = 250.f; // 벌목/채광 거리 (적절히 조절 가능)
    FVector End = Start + Forward * TraceDistance;

    // 3. 충돌 파라미터 설정
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(OwnerActor); // 자신은 무시

    // 4. 실제 라인 트레이스 수행
    GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility, // 또는 커스텀 채널: ECC_GameTraceChannel1 등
        TraceParams
    );

    // 5. 디버그용 선 그리기 (테스트 시에만)
#if WITH_EDITOR
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.f, 0, 1.5f);
    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 12, FColor::Red, false, 0.f);
    }
#endif


    PerformByResourceType();
}

