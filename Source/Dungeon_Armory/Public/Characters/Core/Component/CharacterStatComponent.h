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

// --- HP & MP ���� ���� ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | HP & MP")
    float MaxHealth = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat | HP & MP")
    float CurrentHealth;

// --- ���ݷ� ���� ���� ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Attack | Damage")
    float BaseAttackDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Attack | Speed")
	float BaseAttackSpeed = 1.0f;   // �ʴ� ���� Ƚ��

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Attack | Ciritical")
    float CriticalChance = 0.2f;    // ũ��Ƽ�� Ȯ��

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Attack | Ciritical")
    float CriticalFactor = 1.5f;    // ũ��Ƽ�� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Attack | Logic")
	float AttackRange = 150.0f;     // ���� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Attack | Logic")
    float AttackRadius = 50.0f;     // ���� �ݰ�

public:
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Damage")
    float GetAttackCooldown() const { return 1.0f / FMath::Max(BaseAttackSpeed, 0.01f); }

    UFUNCTION(BlueprintCallable, Category = "Damage")
    float GetAttackPlayRate(float AnimationLength) const { return (AnimationLength < GetAttackCooldown()) ? 1.0f : (BaseAttackSpeed * AnimationLength);
    }


// --- ���� ���� ���� ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Defense")
    float Defense = 5.f;


// --- �̵� �ӵ� ���� ���� ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Speed")
    float BaseSpeed = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Speed")
    float IdleSpeedFactor = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Speed")
    float PatrolSpeedFactor = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Speed")
    float ChaseSpeedFactor = 1.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Speed")
    float DeadSpeedFactor = 0.0f;

// --- �̵� �Ÿ� ���� ��ġ ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Distance")
    float PatrolRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Distance")
	float AttackableDistance = 100.0f;

// --- AI Perception ���� ��ġ ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | AI Perception")
    float SightRadius = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | AI Perception")
    float LoseSightRadius = 700.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | AI Perception")
    float PeripheralVisionAngleDegrees = 90.0f;

// --- Function ---
public:
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
