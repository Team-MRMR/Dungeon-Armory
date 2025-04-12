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
    }
}

void UViewModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateViewMode(DeltaTime);
}

void UViewModeComponent::SetIndoorState(bool bIndoor)
{
    bIsIndoor = bIndoor;
    InterpAlpha = 0.0f;
}

void UViewModeComponent::UpdateViewMode(float DeltaTime)
{
    if (!Camera || !SpringArm)
        return;

    FVector CurrentCameraPos = Camera->GetRelativeLocation();
    FVector TargetCameraPos = (bIsIndoor ? FPSCameraPosition : TPSCameraPosition);
    float CurrentArmLength = SpringArm->TargetArmLength;
    float TargetArmLength = (bIsIndoor ? FPSTargetArmLength : TPSTargetArmLength);

    bool bNeedsCameraLerp = !CurrentCameraPos.Equals(TargetCameraPos, 1.f);
    bool bNeedsArmLerp = !FMath::IsNearlyEqual(CurrentArmLength, TargetArmLength, 1.f);

    if (!bNeedsCameraLerp && !bNeedsArmLerp)
        return;

    if (InterpAlpha == 0.f)
    {
        EViewMode NewMode = bIsIndoor ? EViewMode::FPS : EViewMode::TPS;
        InitializeViewModeSettings(NewMode);
    }

    InterpAlpha += DeltaTime * InterpSpeed;
    InterpAlpha = FMath::Clamp(InterpAlpha, 0.f, 1.f);

    ApplyCameraTransform(InterpAlpha);
    ApplySpringArmTransform(InterpAlpha);

    if (InterpAlpha >= 1.f)
    {
        CurrentViewMode = (bIsIndoor ? EViewMode::FPS : EViewMode::TPS);
        FinalizeViewModeSettings(CurrentViewMode);
    }
}

void UViewModeComponent::ApplyCameraTransform(float Alpha)
{
    if (!Camera)
        return;

    FVector From = (CurrentViewMode == EViewMode::FPS) ? FPSCameraPosition : TPSCameraPosition;
    FVector To = (TargetViewMode == EViewMode::FPS) ? FPSCameraPosition : TPSCameraPosition;

    FVector NewCameraPosition = FMath::Lerp(From, To, Alpha);
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

void UViewModeComponent::InitializeViewModeSettings(EViewMode Mode)
{
    if (!SpringArm || !Camera)
        return;

    if (Mode == EViewMode::FPS)
    {
        SpringArm->bUsePawnControlRotation = false;
    }
    else // TPS
    {
        SpringArm->bUsePawnControlRotation = true;
    }
}


void UViewModeComponent::FinalizeViewModeSettings(EViewMode Mode)
{
    if (!SpringArm)
        return;

    float FinalLength = (Mode == EViewMode::FPS) ? FPSTargetArmLength : TPSTargetArmLength;
    SpringArm->TargetArmLength = FinalLength;
}
