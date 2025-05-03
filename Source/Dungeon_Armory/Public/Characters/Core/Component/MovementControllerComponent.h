// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "MovementControllerComponent.generated.h"

class ACharacter;
class UCharacterMovementComponent;
class UCharacterStatComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementCompleted);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UMovementControllerComponent : public UActorComponent
{
	GENERATED_BODY()


/***** Unreal *****/
public:	
	UMovementControllerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

/***** Movement *****/
public:
	UPROPERTY(BlueprintAssignable)
	FOnMovementCompleted OnMovementCompleted;

private:
	ACharacter* CharacterOwner;
	UCharacterMovementComponent* MovementComponent;
	UCharacterStatComponent* StatComponent;

public:
	void PatrolAtBase(const FVector& Destination, const float AcceptableRadius);
	void ChaseToTarget();
	void ReturnToBase();
	void MoveToDestination(const FVector& Destination, const float AcceptableRadius);
		
private:
	void StopMovement();
};
