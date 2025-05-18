// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Characters/Core/Stat/StaminaStat.h"

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

UENUM(BlueprintType)
enum class EElementalType : uint8
{
	None,   // ����

    Aqua,   // ��
    Ignis,  // ��
	Terra   // ��
};

constexpr float ElementalCompatibility[4][4] =
{
    // None, Aqua, Ignis, Terra
    {1.0f, 1.0f, 1.0f, 1.0f}, // None
    {1.0f, 1.0f, 1.2f, 0.8f}, // Aqua
    {1.0f, 0.8f, 1.0f, 1.2f}, // Ignis
    {1.0f, 1.2f, 0.8f, 1.0f}, // Terra
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

// --- HP���� ���� ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | HP")
    float MaxHealth = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat | HP")
    float CurrentHealth;

// --- Stamina ���� ���� ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Stamina")
    FStaminaStat AttackStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Stamina")
    FStaminaStat SkillStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Stamina")
    FStaminaStat LoggingStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Stamina")
    FStaminaStat MiningStamina;

// --- �÷��̾� �� ���� �Ӽ� ���� ���� ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Elemental")
	EElementalType WeaponElementType = EElementalType::None;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat | Attack | Ciritical")
    bool bIsCritical = false;       // ũ��Ƽ�� ����

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
    float GetAttackPlayRate(float AnimationLength) const
    { return (AnimationLength < GetAttackCooldown()) ? 1.0f : (BaseAttackSpeed * AnimationLength); }

// --- ���� ���� ���� ---
public:
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

// --- ���� ���� ��ġ ---

// --- ä�� ���� ��ġ ---

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
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetSpeedForState(EMobState State);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetSpeedForState(EMobState State) const;

public:
    //UFUNCTION(BlueprintCallable, Category = "Stamina")
    void ConsumeAttackStamina();
    void ConsumeSkillStamina();
    void ConsumeLoggingStamina();
    void ConsumeMiningStamina();

private:
    void ResetSpeed();
    void ApplySpeedModifier(float SpeedMultiplier, float Duration);
    void SetSpeed(float NewSpeed);
};

