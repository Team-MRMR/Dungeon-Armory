#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "HealthStat.generated.h"

UCLASS(Blueprintable)
class DUNGEON_ARMORY_API UHealthStat : public UObject
{
    GENERATED_BODY()

public:
    /** �ִ� ���¹̳� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float Max = 100.f;

    /** ȸ�� �ӵ� (�ʴ� ȸ����) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float RegenRate = 5.f;

    /** ȸ�� üũ �ֱ� (��) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float RegenSpeed = 1.0f;

public:
    /** ���� ���� �� �ʱ�ȭ */
    void Initialize(UObject* WorldContextObject);

    /** ���¹̳� �Һ� */
    void Consume(float Amount);

    /** ���¹̳� ȸ�� Ÿ�̸� ���� */
    UFUNCTION()
    void StopConsume();

    /** ȸ�� ó�� */
    void ApplyRegen(double CurrentTime);

    /** ���� ���¹̳� ��ȯ */
    float GetStamina();

    /** ���� ���¹̳� ��ġ ���� ��ȯ */
    float GetCurrent() const;

    /** �ִ� ���¹̳ʷ� ȸ�� */
    void RestoreFull();

    /** �� ���� Ȯ�� */
    bool IsDepleted() const;

private:
    float Current = 100.f;
    double LastConsumedTime = 0.0;
    double LastCalculatedTime = 0.0;
    bool bIsBeingConsumed = false;

    UWorld* World = nullptr;
    FTimerHandle ConsumeTimerHandle;
};
