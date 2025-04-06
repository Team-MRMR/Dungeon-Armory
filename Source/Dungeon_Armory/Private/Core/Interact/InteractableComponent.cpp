// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Interact/InteractableComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractableComponent::Interact_Implementation(AActor* Caller)
{
    UE_LOG(LogTemp, Log, TEXT("Interacted with: %s by %s"), *GetOwner()->GetName(), *Caller->GetName());
    // 실제 로직은 여기서 구현
}

bool UInteractableComponent::CanInteract_Implementation(AActor* Interactor)
{
	return bIsInteractable;
}

void UInteractableComponent::EnableOutline_Implementation()
{
    if (AActor* Owner = GetOwner())
    {
        TArray<UPrimitiveComponent*> Components;
        Owner->GetComponents(Components);

        for (auto Comp : Components)
        {
            if (Comp) Comp->SetRenderCustomDepth(true);
        }
    }
}

void UInteractableComponent::DisableOutline_Implementation()
{
    if (AActor* Owner = GetOwner())
    {
        TArray<UPrimitiveComponent*> Components;
        Owner->GetComponents(Components);

        for (auto Comp : Components)
        {
            if (Comp) Comp->SetRenderCustomDepth(false);
        }
    }
}
