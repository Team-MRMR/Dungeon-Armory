// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GenericTeamAgentInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "MobBase.generated.h"

class UCharacterStatComponent;
class UTeamComponent;
class UBlackboardComponent;

class AAIController;

UENUM(BlueprintType)
enum class EMobState : uint8
{
    Idle,
    Patrol,
    Chase,
    Battle,
    Dead
};

UCLASS()
class DUNGEON_ARMORY_API AMobBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

/***** Unreal *****/
public:
	AMobBase();

protected:
	virtual void BeginPlay() override;

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

/***** Team *****/
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
	UTeamComponent* TeamComponent;

/***** State *****/
private:
    // ������ Ű �̸� ���
    static const FName MobStateKey;

    EMobState CurrentState;

    UPROPERTY()
    class AAIController* MobAIController;

    UPROPERTY()
    UBlackboardComponent* MobBlackboardComponent;

public:
    void SetMobState(EMobState NewState);

/***** Stat *****/
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UCharacterStatComponent* StatComponent;

public:
    // ü�� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Stat")
    void ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Stat")
    bool IsDead() const;

    // ���¿� ���� �ӵ� ����
    UFUNCTION(BlueprintCallable, Category = "Stat")
    void SetSpeedForState(EMobState State);

private:
    void ResetSpeed();
    void ApplySpeedModifier(float SpeedMultiplier, float Duration);
    void SetSpeed(float NewSpeed);

    // ���¿� ���� �ӵ� ��ȯ
    UFUNCTION(BlueprintCallable, Category = "Stat")
    float GetSpeedForState(EMobState State) const;
};
