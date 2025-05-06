// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Core/Interact/Interface/Interactable.h"

#include "InteractableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class DUNGEON_ARMORY_API UInteractableComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:
	UInteractableComponent();

/***** Interact *****/
protected:
	UPROPERTY(EditAnywhere)
	bool bIsInteractable = true;

public:
	// ��ȣ�ۿ� ���� �Ǵ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool CanInteract(AActor* Interactor);

	// ��ȣ�ۿ� ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);

	// �ƿ����� ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void EnableOutline();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DisableOutline();

};
