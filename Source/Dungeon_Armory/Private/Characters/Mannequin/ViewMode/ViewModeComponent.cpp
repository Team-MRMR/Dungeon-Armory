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
		UE_LOG(LogTemp, Error, TEXT("ViewModeComponent: SpringArm �Ǵ� CameraComponent�� �������� �ʽ��ϴ�."));
		return;
	}

	CurrentViewMode = EViewMode::TPS;
	ApplyViewMode(CurrentViewMode); // �ʱ� ���� ����
}


// Called every frame
void UViewModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!SpringArm) return;

	// ī�޶� �Ÿ� �ε巴�� ��ȯ
	float CurrentLength = SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::FInterpTo(CurrentLength, TargetArmLength, DeltaTime, InterpSpeed);

	// ī�޶� ȸ�� �ε巴�� ��ȯ
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
		TargetRotation = OwnerCharacter->GetControlRotation(); // TPS ���� ���� �þ�
	}
}
