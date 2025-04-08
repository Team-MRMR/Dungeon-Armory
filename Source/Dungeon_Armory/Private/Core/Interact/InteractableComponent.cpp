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
    // ���� ������ ���⼭ ����
}

bool UInteractableComponent::CanInteract_Implementation(AActor* Interactor)
{
	return bIsInteractable;
}

void UInteractableComponent::EnableOutline_Implementation()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;

	TArray<UStaticMeshComponent*> MeshComponents;
	OwnerActor->GetComponents<UStaticMeshComponent>(MeshComponents);

	UE_LOG(LogTemp, Warning, TEXT("Outside Enabling outline"));
	for (auto* MeshComp : MeshComponents)
	{
		if (MeshComp)
		{
			MeshComp->SetRenderCustomDepth(true);
			MeshComp->SetCustomDepthStencilValue(1); // ��: ���̶���Ʈ�� ���ٽ� ��
			UE_LOG(LogTemp, Warning, TEXT("Inside Enabled outline for: %s"), *MeshComp->GetName());
		}
	}
}

void UInteractableComponent::DisableOutline_Implementation()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;

	TArray<UStaticMeshComponent*> MeshComponents;
	OwnerActor->GetComponents<UStaticMeshComponent>(MeshComponents);

	UE_LOG(LogTemp, Warning, TEXT("Outside Disabling outline"));
	for (auto* MeshComp : MeshComponents)
	{
		if (MeshComp)
		{
			MeshComp->SetRenderCustomDepth(false);
			UE_LOG(LogTemp, Warning, TEXT("Inside Disabled outline for: %s"), *MeshComp->GetName());
		}
	}
}
