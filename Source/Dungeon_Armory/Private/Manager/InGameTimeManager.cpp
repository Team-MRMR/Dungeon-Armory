// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/InGameTimeManager.h"

UInGameTimeManager::UInGameTimeManager()
{

}

void UInGameTimeManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TManagerBase<UInGameTimeManager>::InitializeInstance(this);

	StartTimer();
}

void UInGameTimeManager::Deinitialize()
{
    Super::Deinitialize();

    // Ÿ�̸� ����
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
    }
}

UInGameTimeManager* UInGameTimeManager::GetInstance()
{
	auto Instance = TManagerBase<UInGameTimeManager>::GetInstance();
	if (Instance)
	{
		return Instance;
	}

	return nullptr;
}

void UInGameTimeManager::StartTimer()
{
    if (GetWorld())
    {
        // ���� �ֱ�� UpdateTime() ȣ�� (1�ʸ��� ����)
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UInGameTimeManager::UpdateTime, 1.0f, true);
    }
}

void UInGameTimeManager::UpdateTime()
{
    // �ð� ���� ��� (Time Scale)
    CurrInGameTime.AddMinutes(TimeScale);

	//if (3.0f <= CurrInGameTime.Minutes && CurrInGameTime.Minutes < 4.0f)
    //{
    //    // �ð� ���� �̺�Ʈ ȣ��
    //    OnTimePeriodChanged.Broadcast();
    //}

}
