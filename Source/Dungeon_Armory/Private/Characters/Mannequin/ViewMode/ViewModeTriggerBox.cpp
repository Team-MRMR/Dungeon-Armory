// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Mannequin/ViewMode/ViewModeTriggerBox.h"
#include "GameFramework/Character.h"

AViewModeTriggerBox::AViewModeTriggerBox()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AViewModeTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &AViewModeTriggerBox::OnTriggerBeginOverlap);
    OnActorEndOverlap.AddDynamic(this, &AViewModeTriggerBox::OnTriggerEndOverlap);
}

void AViewModeTriggerBox::OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    ACharacter* Character = Cast<ACharacter>(OtherActor);
    if (!Character)
        return;

    UViewModeComponent* ViewModeComponent = Character->FindComponentByClass<UViewModeComponent>();
    if (ViewModeComponent)
    {
        ViewModeComponent->SetIndoorState(true); // 실내로 진입
    }
}

void AViewModeTriggerBox::OnTriggerEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    ACharacter* Character = Cast<ACharacter>(OtherActor);
    if (!Character)
        return;

    UViewModeComponent* ViewModeComponent = Character->FindComponentByClass<UViewModeComponent>();
    if (ViewModeComponent)
    {
        ViewModeComponent->SetIndoorState(false); // 실외로 나감
    }
}
