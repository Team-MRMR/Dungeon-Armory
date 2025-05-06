// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CharacterStatComponent.generated.h"

UENUM(BlueprintType)
enum class EMobState : uint8
{
    Idle,
    Patrol,
    Chase,
    Battle,
    Dead
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

/***** Character *****/
private:
    ACharacter* OwnerCharacter;

// --- HP & MP 관련 스탯 ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float MaxHealth = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat")
    float CurrentHealth;

// --- 공격 & 방어 관련 스탯 ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseAttackDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseAttackSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float Defense = 5.f;


// --- 이동 속도 관련 스탯 ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseSpeed = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float IdleSpeedFactor = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float PatrolSpeedFactor = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float ChaseSpeedFactor = 1.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float DeadSpeedFactor = 0.0f;

// --- 이동 거리 관련 수치 ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Distance")
    float PatrolRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Distance")
	float AcceptableRadius = 100.0f;

// --- AI Perception 관련 수치 ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
    float SightRadius = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
    float LoseSightRadius = 700.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
    float PeripheralVisionAngleDegrees = 90.0f;

// --- Function ---
public:
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Dead")
    bool IsDead() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetSpeedForState(EMobState State);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetSpeedForState(EMobState State) const;

private:
    void ResetSpeed();
    void ApplySpeedModifier(float SpeedMultiplier, float Duration);
    void SetSpeed(float NewSpeed);
};
