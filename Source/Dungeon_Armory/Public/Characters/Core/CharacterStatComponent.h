// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
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

public:
    // --- ���� (���� �Ӽ�) ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float MaxHealth = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float Defense = 5.f;

    // --- �̵� �ӵ� ���º� ���� ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float IdleSpeed = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float PatrolSpeed = 250.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float ChaseSpeed = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CombatSpeed = 350.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float DeadSpeed = 0.f;

public:
    void ResetSpeed();
    void ApplySpeedModifier(float SpeedMultiplier, float Duration);
    void SetMovementSpeed(float NewSpeed);

public:
    // ���¿� ���� �ӵ� ��ȯ
    UFUNCTION(BlueprintCallable, Category = "Stat")
    float GetSpeedForState(ECharacterState State) const;

    // ü�� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Stat")
    void ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Stat")
    bool IsDead() const;
		
};
