// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Mannequin/ViewMode/ViewModeComponent.h"

#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

UViewModeComponent::UViewModeComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UViewModeComponent::BeginPlay()
{
    Super::BeginPlay();

    OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter)
    {
        SpringArm = OwnerCharacter->FindComponentByClass<USpringArmComponent>();
        
        Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();
		if (Camera)
		{
			// 카메라의 초기 위치를 저장
			Camera->GetRelativeLocation() = TPSCameraPosition;
		}
    }
}

void UViewModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateViewMode(DeltaTime);
}

void UViewModeComponent::SetIndoorState(bool bIndoor)
{
    EViewMode DesiredMode = bIndoor ? EViewMode::FPS : EViewMode::TPS;

    if (TargetViewMode != DesiredMode)
    {
        bIsIndoor = bIndoor;
        TargetViewMode = DesiredMode;
        InterpAlpha = 0.0f;
    }
}

void UViewModeComponent::UpdateViewMode(float DeltaTime)
{
    if (CurrentViewMode == TargetViewMode)
    {
        // 위치 또는 길이가 일치하지 않으면 다시 보간
        const float Tolerance = 1.0f;
        FVector TargetCameraPos = (TargetViewMode == EViewMode::FPS) ? FPSCameraPosition : TPSCameraPosition;
        float TargetArmLength = (TargetViewMode == EViewMode::FPS) ? FPSTargetArmLength : TPSTargetArmLength;

        bool bNeedCorrection = !Camera->GetRelativeLocation().Equals(TargetCameraPos, Tolerance) ||
            !FMath::IsNearlyEqual(SpringArm->TargetArmLength, TargetArmLength, Tolerance);

        if (bNeedCorrection)
        {
            InterpAlpha = 0.0f;
        }

        return;
    }

    InterpAlpha += DeltaTime * InterpSpeed;
    InterpAlpha = FMath::Clamp(InterpAlpha, 0.f, 1.f);

    ApplyCameraTransform(InterpAlpha);
    ApplySpringArmTransform(InterpAlpha);

    if (InterpAlpha >= 1.f)
    {
        CurrentViewMode = TargetViewMode;
        SpringArm->TargetArmLength = (TargetViewMode == EViewMode::FPS) ? FPSTargetArmLength : TPSTargetArmLength;
    }
}

void UViewModeComponent::ApplyCameraTransform(float Alpha)
{
    if (!Camera)
        return;

    FVector FromPos = (CurrentViewMode == EViewMode::FPS) ? FPSCameraPosition : TPSCameraPosition;
    FVector ToPos = (TargetViewMode == EViewMode::FPS) ? FPSCameraPosition : TPSCameraPosition;

    FVector NewCameraPosition = FMath::Lerp(FromPos, ToPos, Alpha);
    Camera->SetRelativeLocation(NewCameraPosition);
}

void UViewModeComponent::ApplySpringArmTransform(float Alpha)
{
    if (!SpringArm)
        return;

    float FromLength = (CurrentViewMode == EViewMode::FPS) ? FPSTargetArmLength : TPSTargetArmLength;
    float ToLength = (TargetViewMode == EViewMode::FPS) ? FPSTargetArmLength : TPSTargetArmLength;

    float NewLength = FMath::Lerp(FromLength, ToLength, Alpha);
    SpringArm->TargetArmLength = NewLength;
}