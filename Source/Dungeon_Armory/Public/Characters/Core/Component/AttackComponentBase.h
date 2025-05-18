// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponentBase.generated.h"

class UAnimMontage;
class UCharacterStatComponent;

UCLASS(Abstract)
class DUNGEON_ARMORY_API UAttackComponentBase : public UActorComponent
{
	GENERATED_BODY()

/***** Unreal *****/
public:	
	// Sets default values for this component's properties
	UAttackComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

/***** Attack *****/
protected:
	UAnimInstance* AnimInstance;
	UCharacterStatComponent* Stat;

public:
    virtual void StartAttack();   // �ܺο��� ���� ���� �� ȣ��
    virtual void OnAttack();      // AttackNotify���� ȣ��
	virtual void OnAttackEnd();   // AttackNotify���� ȣ��

protected:
	virtual float CalculateDamage(UCharacterStatComponent* Attacker, UCharacterStatComponent* Defender);
};
