// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Interact/InteractionComponent.h"
#include "Core/Interact/InteractableComponent.h"
#include "Core/Interact/Interface/Interactable.h"

#include "Characters/Mannequin/Manny.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentTarget = nullptr;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
    OwnerActor = GetOwner();
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TraceForInteractable();
}

void UInteractionComponent::TryInteract()
{
    if (CurrentTarget)
    {
        UInteractableComponent* InteractableComp = CurrentTarget->FindComponentByClass<UInteractableComponent>();
        if (InteractableComp && InteractableComp->CanInteract(GetOwner()))
        {
			UE_LOG(LogTemp, Warning, TEXT("UInteractionComponent::TryInteract() Called"));
            InteractableComp->Interact(GetOwner());
        }
    }
}

void UInteractionComponent::TraceForInteractable()
{
    if (!OwnerActor)
        return;

    FVector Start, End;
    FRotator ViewRot;
    OwnerActor->GetActorEyesViewPoint(Start, ViewRot);
    End = Start + ViewRot.Vector() * TraceDistance;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(OwnerActor);

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
    AActor* HitActor = bHit ? Hit.GetActor() : nullptr;

    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.01f, 0, 2.0f);

    // 이미 동일한 대상이면 무시
    if (HitActor == CurrentTarget) return;

    // 이전 강조 해제
    if (CurrentTarget)
    {
        UInteractableComponent* PrevInteractable = CurrentTarget->FindComponentByClass<UInteractableComponent>();
        if (PrevInteractable)
        {
            PrevInteractable->DisableOutline();
        }
    }

    CurrentTarget = nullptr;

    // 새 대상 설정
    if (HitActor)
    {
        UInteractableComponent* NewInteractable = HitActor->FindComponentByClass<UInteractableComponent>();
        if (NewInteractable && NewInteractable->CanInteract(OwnerActor))
        {
            NewInteractable->EnableOutline();
            CurrentTarget = HitActor;
        }
    }
}
