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

/***** Stat *****/
public:
    // --- 스탯 (공통 속성) ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float MaxHealth = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float Defense = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseSpeed = 250;

// --- 상태 변화에 따른 속도 변화 계수---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float IdleSpeedFactor = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float PatrolSpeedFactor = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float ChaseSpeedFactor = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float DeadSpeedFactor = 0.f;

// --- 거리 관련 수치 ---
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

public:
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Dead")
    bool IsDead() const;

    // 상태에 따라 속도 적용
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetSpeedForState(EMobState State);

private:
    void ResetSpeed();
    void ApplySpeedModifier(float SpeedMultiplier, float Duration);
    void SetSpeed(float NewSpeed);

    // 상태에 따라 속도 반환
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetSpeedForState(EMobState State) const;
};