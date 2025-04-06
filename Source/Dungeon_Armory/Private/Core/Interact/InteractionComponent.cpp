// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Interact/InteractionComponent.h"
#include "Core/Interact/Interface/Interactable.h"

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

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TraceForInteractable();
}

void UInteractionComponent::TryInteract()
{
    if (CurrentTarget && CurrentTarget->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
    {
        if (IInteractable::Execute_CanInteract(CurrentTarget, GetOwner()))
        {
            IInteractable::Execute_Interact(CurrentTarget, GetOwner());
        }
    }
}

void UInteractionComponent::TraceForInteractable()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    FVector Start, End;
    FRotator ViewRot;
    Owner->GetActorEyesViewPoint(Start, ViewRot);
    End = Start + ViewRot.Vector() * TraceDistance;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
    AActor* HitActor = bHit ? Hit.GetActor() : nullptr;

    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.01f, 0, 2.0f);

    // 이미 동일한 대상이면 무시
    if (HitActor == CurrentTarget) return;

    // 이전 강조 해제
    if (CurrentTarget && CurrentTarget->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
    {
        IInteractable::Execute_DisableOutline(CurrentTarget);
    }

    CurrentTarget = nullptr;

    // 새 대상 설정
    if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
    {
        if (IInteractable::Execute_CanInteract(HitActor, GetOwner()))
        {
            IInteractable::Execute_EnableOutline(HitActor);
            CurrentTarget = HitActor;
        }
    }
}
