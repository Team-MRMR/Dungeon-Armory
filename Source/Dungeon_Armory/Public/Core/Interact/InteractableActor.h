// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Core/Interact/Interface/Interactable.h"

#include "InteractableActor.generated.h"

UCLASS()
class DUNGEON_ARMORY_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


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
