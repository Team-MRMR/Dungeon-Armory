// Fill out your copyright notice in the Description page of Project Settings.

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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UViewModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UViewModeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


/***** View Mode *****/

private:
	UPROPERTY()
	USpringArmComponent* SpringArm;

	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "View Mode")
	float TPSArmLength = 300.f;

	UPROPERTY(EditAnywhere, Category = "View Mode")
	float FPSArmLength = 0.f;

	UPROPERTY(EditAnywhere, Category = "View Mode")
	float InterpSpeed = 5.f;

	EViewMode CurrentViewMode;
	float TargetArmLength;
	FRotator TargetRotation;

public:
	/** 시점 전환 요청 함수 */
	void RequestViewMode(EViewMode NewMode);

	/** 현재 시점 조회 */
	EViewMode GetCurrentViewMode() const { return CurrentViewMode; }

private:
	/** 시점 전환 로직 */
	void ApplyViewMode(EViewMode NewMode);
};
