// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Core/CharacterStatComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	OwnerCharacter= Cast<ACharacter>(GetOwner());
}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	// ...
	
}
