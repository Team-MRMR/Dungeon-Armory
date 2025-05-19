#pragma once

#include "CoreMinimal.h"

#include "StaminaStat.generated.h"

USTRUCT(BlueprintType)
struct DUNGEON_ARMORY_API FStaminaStat
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Max = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackConsumption = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillConsumption = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LoggingConsumption = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MiningConsumption = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regen")
    float Regen = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regen")
    float RegenDelay = 1.0f;

    float Current = 100.f;
    double StartRegenTime = 0.0;
    bool bIsBeingConsumed = false;

    UWorld* World = nullptr;
    FTimerHandle ConsumeTimerHandle;
    FTimerDelegate ConsumeTimerDelegate;

    /** ���� ���� �� �ʱ�ȭ */
    void Initialize(UWorld* WorldObject)
    {
        World = WorldObject;
		if (!World)
			return;

        Current = Max;
        StartRegenTime = 0.0;
        bIsBeingConsumed = false;

        // ���� ��������Ʈ�� StopConsume ���ε�
        ConsumeTimerDelegate.BindLambda([this]() { this->StopConsume(); });
    }

    /** ���¹̳� �Һ� */
    void Consume(float Amount)
    {
		UE_LOG(LogTemp, Warning, TEXT("Consume called!"));
        if (!World)
            return;

        ApplyRegen();
        Current = FMath::Clamp(Current - Amount, 0.f, Max);
        bIsBeingConsumed = true;

        // Ÿ�̸� ����
        World->GetTimerManager().SetTimer(
            ConsumeTimerHandle,
            ConsumeTimerDelegate,
            RegenDelay,
            false
        );
    }

    /** ���¹̳� ȸ�� Ÿ�̸� ���� */
    void StopConsume()
    {
		 UE_LOG(LogTemp, Warning, TEXT("StopConsume called!"));

        const double CurrentTime = World->GetTimeSeconds();
        StartRegenTime = CurrentTime;

        bIsBeingConsumed = false;
    }

	float GetCurrent()
	{   
		ApplyRegen();   // ȸ���Ͽ� ��ġ ����
		return Current;
	}

    /** ȸ�� ó�� */
    void ApplyRegen()
    {
        if (!World)
            return;

        if (bIsBeingConsumed)
            return;

        const double CurrentTime = World->GetTimeSeconds();
        const double Delta = CurrentTime - StartRegenTime;

        if (Delta <= 0.0)
            return;

        const float RegenAmount = Regen * Delta;
        Current = FMath::Clamp(Current + RegenAmount, 0.f, Max);

		UE_LOG(LogTemp, Warning, TEXT("Regen called! Current: %f"), Current);
    }
};
