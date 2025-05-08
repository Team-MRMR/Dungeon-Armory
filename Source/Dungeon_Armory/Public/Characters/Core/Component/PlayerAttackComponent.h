// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Core/Component/AttackComponentBase.h"
#include "PlayerAttackComponent.generated.h"

class UAnimMontage;
class UCharacterStatComponent;

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API UPlayerAttackComponent : public UAttackComponentBase
{
	GENERATED_BODY()

/***** Attack *****/
private:
    UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
    UAnimMontage* ComboAttackMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
    TArray<FName> ComboAttackSections;

    ACharacter* OwnerCharacter;
    UAnimInstance* AnimInstance;
    UCharacterStatComponent* StatComponent;

    int32 CurrentComboIndex; // ���� �޺� �ε���

    bool bIsMontageEnded;   // ��Ÿ�� ���� ����
    bool bCanReceiveInput;  // �޺� �Է� ���� ����
    bool bNextCombo;        // ���� �޺� ���� ����

    FTimerHandle ComboInputTimerHandle;  // �޺� ���ӽð� �ڵ鷯

    /***** Unreal *****/
public:
    UPlayerAttackComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    /***** Attack *****/
public:
    void StartAttack();     // �ܺο��� ���� ���� �� ȣ��
    void OnAttack();     // AttackNotify���� ȣ��
    void ReceiveInput();    // �޺� �Է� ����
    void OnAttackEnded();

protected:
    void ProceedCombo();
    void PlayComboAttackMontage(int32 ComboIndex);
};
