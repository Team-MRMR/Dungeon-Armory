// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mannequin/ViewMode/CameraTriggerVolume.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ACameraTriggerVolume::ACameraTriggerVolume()
{

}

void ACameraTriggerVolume::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &ACameraTriggerVolume::HandleTriggerBeginOverlap);
}

void ACameraTriggerVolume::HandleTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (ACharacter* Character = Cast<ACharacter>(OtherActor))
    {
        if (UViewModeComponent* ViewComp = Character->FindComponentByClass<UViewModeComponent>())
        {
			ViewModeToApply = ViewComp->GetCurrentViewMode() == EViewMode::FPS ? EViewMode::TPS : EViewMode::FPS; // 현재 모드와 반대 모드로 전환
            ViewComp->RequestViewMode(ViewModeToApply);  // ViewModeComponent에게 위임
        }
    }
}