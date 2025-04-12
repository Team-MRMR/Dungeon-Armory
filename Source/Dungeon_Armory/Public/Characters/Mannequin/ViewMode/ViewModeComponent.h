#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ViewModeComponent.generated.h"

UENUM(BlueprintType)
enum class EViewMode : uint8
{
    TPS UMETA(DisplayName = "ThirdPerson"),
    FPS UMETA(DisplayName = "FirstPerson")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEON_ARMORY_API UViewModeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UViewModeComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetIndoorState(bool bIndoor);

private:
    void UpdateViewMode(float DeltaTime);
    void ApplyCameraTransform(float Alpha);
    void ApplySpringArmTransform(float Alpha);

private:
    ACharacter* OwnerCharacter = nullptr;
    USpringArmComponent* SpringArm = nullptr;
    UCameraComponent* Camera = nullptr;

    EViewMode CurrentViewMode = EViewMode::TPS;
    EViewMode TargetViewMode = EViewMode::TPS;

    bool bIsIndoor = false;

    float InterpAlpha = 1.0f;

    UPROPERTY(EditAnywhere, Category = "ViewMode | Interp")
    float InterpSpeed = 5.0f;

    UPROPERTY(EditAnywhere, Category = "ViewMode | FPS")
    FVector FPSCameraPosition = FVector(10.0, 0.0f, 0.0f);

    UPROPERTY(EditAnywhere, Category = "ViewMode | TPS")
    FVector TPSCameraPosition = FVector(50.0f, 40.0f, 50.0f);

    UPROPERTY(EditAnywhere, Category = "ViewMode | FPS")
    float FPSTargetArmLength = 0.0f;

    UPROPERTY(EditAnywhere, Category = "ViewMode | TPS")
    float TPSTargetArmLength = 400.0f;
};
