// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Manager/ManagerBase.h"

#include "InGameTimeManager.generated.h"

UENUM(BlueprintType)
enum class EInGameTimePeriod : uint8
{
    Dawn,       // ���� (0�� ~ 6��)
    Morning,    // ��ħ (6�� ~ 12��)
    Afternoon,  // ���� (12�� ~ 18��)
    Night       // ��   (18�� ~ 24��)
};

USTRUCT(BlueprintType)
struct FInGameTime
{
    GENERATED_BODY()

    /***** Variables *****/
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In-Game Time")
    EInGameTimePeriod Period;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In-Game Time")
    int32 Hours = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In-Game Time")
    float Minutes = 0;

    /***** Functions *****/
public:
    // �ð��� ������Ű�� �Լ�
    void AddMinutes(float DeltaMinutes)
    {
        Minutes += DeltaMinutes;
        while (Minutes >= 60.0f)
        {
            Minutes -= 60.0f;
            Hours++;

            if (Hours >= 24)
            {
                Hours = 0; // �Ϸ簡 ������ 0���� �ʱ�ȭ
            }
        }

        if (0 <= Hours && Hours < 6)
        {
            Period = EInGameTimePeriod::Dawn;
        }
        else if (6 <= Hours && Hours < 12)
        {
            Period = EInGameTimePeriod::Morning;
        }
        else if (12 <= Hours && Hours < 18)
        {
            Period = EInGameTimePeriod::Afternoon;
        }
        else
        {
            Period = EInGameTimePeriod::Night;
        }
    }
};

class ANPCAIController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimePeriodChanged);

UCLASS()
class DUNGEON_ARMORY_API UInGameTimeManager : public UManagerBase
{
	GENERATED_BODY()

/***** Variables *****/
protected:
    UPROPERTY(BlueprintReadOnly, Category = "In-Game Time")
    FInGameTime CurrInGameTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In-Game Time")
    float TimeScale = 1.0f;

private:
    float AccumulatedTime = 0.0f;
    FTimerHandle TimerHandle;

/***** Functions (Unreal) *****/
public:
    UInGameTimeManager();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

/***** Functions (ManagerBase) *****/
public:
	static UInGameTimeManager* GetInstance();

/***** Functions (In-Game Time) *****/
public:
    UPROPERTY(BlueprintAssignable, Category = "In-Game Time")
    FOnTimePeriodChanged OnTimePeriodChanged;

    void StartTimer();
    void UpdateTime();

    UFUNCTION(BlueprintCallable, Category = "In-Game Time")
    FInGameTime GetCurrentInGameTime() const;

    UFUNCTION(BlueprintCallable, Category = "In-Game Time")
    void SetTimeScale(float NewScale) { TimeScale = NewScale; }
};