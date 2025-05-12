// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mannequin/Component/ToolStatComponent.h"

// Sets default values for this component's properties
UToolStatComponent::UToolStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UToolStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UToolStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

