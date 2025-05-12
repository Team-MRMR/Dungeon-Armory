// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mannequin/Component/AxeStatComponent.h"

// Sets default values for this component's properties
UAxeStatComponent::UAxeStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UAxeStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UAxeStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}