#include "Characters/Mannequin/Component/PickaxeStatComponent.h"


UPickaxeStatComponent::UPickaxeStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UPickaxeStatComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UPickaxeStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}