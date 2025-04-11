// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mannequin/ViewMode/ViewModeComponent.h"

#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UViewModeComponent::UViewModeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UViewModeComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) 
		return;

	SpringArm = OwnerCharacter->FindComponentByClass<USpringArmComponent>();
	Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();

	if (!SpringArm || !Camera)
	{
		UE_LOG(LogTemp, Error, TEXT("ViewModeComponent: SpringArm 또는 CameraComponent가 존재하지 않습니다."));
		return;
	}

	CurrentViewMode = EViewMode::TPS;
	ApplyViewMode(CurrentViewMode); // 초기 시점 설정
}


// Called every frame
void UViewModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!SpringArm) return;

	// 카메라 거리 부드럽게 전환
	float CurrentLength = SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::FInterpTo(CurrentLength, TargetArmLength, DeltaTime, InterpSpeed);

	// 카메라 회전 부드럽게 전환
	FRotator CurrentRot = SpringArm->GetComponentRotation();
	SpringArm->SetWorldRotation(FMath::RInterpTo(CurrentRot, TargetRotation, DeltaTime, InterpSpeed));
}

void UViewModeComponent::RequestViewMode(EViewMode NewMode)
{
	if (NewMode == CurrentViewMode)
		return;

	CurrentViewMode = NewMode;
	ApplyViewMode(NewMode);
}

void UViewModeComponent::ApplyViewMode(EViewMode NewMode)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter || !SpringArm)
		return;

	if (NewMode == EViewMode::FPS)
	{
		TargetArmLength = FPSArmLength;
		SpringArm->bUsePawnControlRotation = true;
		TargetRotation = OwnerCharacter->GetControlRotation();
	}
	else if (NewMode == EViewMode::TPS)
	{
		TargetArmLength = TPSArmLength;
		SpringArm->bUsePawnControlRotation = false;
		TargetRotation = OwnerCharacter->GetControlRotation(); // TPS 기준 뒤쪽 시야
	}
}
