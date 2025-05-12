// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Characters/Core/Interface/IDamageable.h"

#include "GatherableActor.generated.h"

UCLASS()
class DUNGEON_ARMORY_API AGatherableActor : public AActor, public IIDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGatherableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float CurrentHealth;


// IIDamageable을(를) 통해 상속됨
public:
	void ReceiveDamage(float DamageAmount) override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Die")
	void Die() override;
	virtual void Die_Implementation(float Damage) { }

};
