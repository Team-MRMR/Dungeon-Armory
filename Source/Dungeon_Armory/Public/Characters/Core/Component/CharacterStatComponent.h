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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float Defense = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float BaseSpeed = 250;

    // --- 상태 변화에 따른 속도 변화 ---
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float IdleSpeedOffset = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float PatrolSpeedOffset = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float ChaseSpeedOffset = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float CombatSpeedOffset = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
    float DeadSpeedOffset = 0.f;

	// --- 이동 거리 관련 수치 ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Distance")
    float PatrolRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Distance")
	float AcceptableRadius = 50.0f;

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


// --- 블랙보드 키값 스트링 캐싱 ---
namespace BBKeys
{
	static const FName CurrentHealth(TEXT("CurrentHealth"));

	static const FName MobState(TEXT("MobState"));
    static const FName PatrolRadius(TEXT("PatrolRadius"));
    static const FName AcceptableRadius(TEXT("AcceptanceRadius"));
}