// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Mannequin/ViewMode/ViewModeTriggerBox.h"
#include "Characters/Mannequin/ViewMode/ViewModeComponent.h"
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

    //// --- �������� Overlapping ���� Ȯ�� �� ó�� ---
    //TArray<AActor*> OverlappingActors;
    //GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

    //for (AActor* Actor : OverlappingActors)
    //{
    //    ACharacter* Character = Cast<ACharacter>(Actor);
    //    if (!Character)
    //        continue;

    //    UViewModeComponent* ViewModeComponent = Character->FindComponentByClass<UViewModeComponent>();
    //    if (ViewModeComponent)
    //    {
    //        ViewModeComponent->SetIndoorState(true); // ���� �� Ʈ���� �ȿ� ������ �ǳ��� ����
    //    }
    //}
}

void AViewModeTriggerBox::OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    ACharacter* Character = Cast<ACharacter>(OtherActor);
    if (!Character)
        return;

    UViewModeComponent* ViewModeComponent = Character->FindComponentByClass<UViewModeComponent>();
    if (ViewModeComponent)
    {
        ViewModeComponent->SetIndoorState(true); // �ǳ��� ����
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
        ViewModeComponent->SetIndoorState(false); // �ǿܷ� ����
    }
}
