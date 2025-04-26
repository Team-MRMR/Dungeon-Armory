// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float BaseSpeed = 250;

    // --- 이동 속도 변화 계수 ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float IdleSpeedOffset = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float PatrolSpeedOffset = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float ChaseSpeedOffset = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CombatSpeedOffset = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float DeadSpeedOffset = 0.f;
};
