// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ManagerBase.generated.h"

/**
 * UManagerBase: ����ý����� �⺻ Ŭ����
 */
UCLASS(Abstract) // ���� �ν��Ͻ�ȭ ����
class DUNGEON_ARMORY_API UManagerBase : public UGameInstanceSubsystem
{
	GENERATED_BODY()
};

/**
 * TManagerBase<T>: ���׸� �̱��� ����ý��� ���� ���ø�
 * (���ø� Ŭ������ ����� ���Ǹ� �и��� �� ����)
 */
template <typename T>
class TManagerBase
{
private:
	static T* Instance;

public:
	/** �ʱ�ȭ (UManagerBase���� ȣ��) */
	static void InitializeInstance(T* NewInstance)
	{
		if (NewInstance)
		{
			Instance = NewInstance;
		}
	}

	/** ���� (UManagerBase���� ȣ��) */
	static void DestroyInstance()
	{
		Instance = nullptr;
	}

	/** �̱��� ��ȯ */
	static T* GetInstance()
	{
		// �̹� ĳ�̵� �ν��Ͻ��� �ִٸ� ��� ��ȯ
		if (Instance)
		{
			return Instance;
		}

		// ĳ�̵� ���� ���ٸ�, �ٽ� ã�� ĳ��
		if (GEngine)
		{
			// ���� Ȱ��ȭ�� ���� ã��
			for (const FWorldContext& Context : GEngine->GetWorldContexts())
			{
				if (Context.World())
				{
					if (UGameInstance* GameInstance = Context.World()->GetGameInstance())
					{
						Instance = GameInstance->GetSubsystem<T>();
						return Instance;
					}
				}
			}
		}
		return nullptr;
	}
};

// ���� ���� ���� (�� �κ��� ���ø��� ���ǵ� ����� ���ԵǾ�� �մϴ�)
template <typename T>
T* TManagerBase<T>::Instance = nullptr;