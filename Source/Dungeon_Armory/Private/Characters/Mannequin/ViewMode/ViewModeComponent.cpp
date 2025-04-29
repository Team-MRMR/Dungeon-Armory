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
			// ī�޶��� �ʱ� ��ġ�� ����
			Camera->GetRelativeLocation() = TPSCameraPosition;
		}

        Mesh = OwnerCharacter->GetMesh();
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
    FVector TargetCameraPos = (TargetViewMode == EViewMode::FPS) ? FPSCameraPosition : TPSCameraPosition;
    float TargetArmLength = (TargetViewMode == EViewMode::FPS) ? FPSTargetArmLength : TPSTargetArmLength;

    FVector CurrentCameraPos = Camera->GetRelativeLocation();
    float CurrentArmLength = SpringArm->TargetArmLength;

    bool bViewModeChanged = (CurrentViewMode != TargetViewMode);

    const float Tolerance = 1.0f;
    bool bNeedCorrection =
        !CurrentCameraPos.Equals(TargetCameraPos, Tolerance) ||
        !FMath::IsNearlyEqual(CurrentArmLength, TargetArmLength, Tolerance);

    if (bViewModeChanged || bNeedCorrection)
    {
        InterpAlpha += DeltaTime * InterpSpeed;
        InterpAlpha = FMath::Clamp(InterpAlpha, 0.0f, 1.0f);

        // Lerp ���� (���� ��ġ�� ��ǥ ��ġ ���̸� ����)
        FVector NewCameraPos = FMath::Lerp(CurrentCameraPos, TargetCameraPos, InterpAlpha);
        float NewArmLength = FMath::Lerp(CurrentArmLength, TargetArmLength, InterpAlpha);

        Camera->SetRelativeLocation(NewCameraPos);
        SpringArm->TargetArmLength = NewArmLength;

        // �޽� ������ ����
        if (Mesh)
        {
            if (InterpAlpha > FPSRenderOffTiming && TargetViewMode == EViewMode::FPS)
            {
                Mesh->SetOwnerNoSee(true);
            }
            else if (InterpAlpha > TPSRenderOffTiming && TargetViewMode == EViewMode::TPS)
            {
                Mesh->SetOwnerNoSee(false);
            }
        }

        if (InterpAlpha >= 1.0f)
        {
            // ���� �Ϸ�
            CurrentViewMode = TargetViewMode;
            InterpAlpha = 0.f; // ���� ������ ���� �ʱ�ȭ
        }
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