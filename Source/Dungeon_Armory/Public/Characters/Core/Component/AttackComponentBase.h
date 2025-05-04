// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponentBase.generated.h"

class UAnimMontage;
class UCharacterStatComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)/*Abstract*/)
class DUNGEON_ARMORY_API UAttackComponentBase : public UActorComponent
{
	GENERATED_BODY()

/***** Attack *****/
private:
    UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
    UAnimMontage* ComboAttackMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
    TArray<FName> ComboAttackSections;

    UPROPERTY()
    ACharacter* OwnerCharacter;

    UPROPERTY()
    UAnimInstance* AnimInstance;

    UPROPERTY()
    UCharacterStatComponent* StatComponent;

	int32 CurrentComboIndex; // ���� �޺� �ε���

	bool bIsMontageEnded;   // ��Ÿ�� ���� ����
	bool bCanReceiveInput;  // �޺� �Է� ���� ����
	bool bNextCombo;        // ���� �޺� ���� ����

    FTimerHandle ComboInputTimerHandle;  // �޺� ���ӽð� �ڵ鷯

/***** Unreal *****/
public:	
	// Sets default values for this component's properties
	UAttackComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

/***** Attack *****/
public:
    void StartAttack();     // �ܺο��� ���� ���� �� ȣ��
    void OnAttackHit();     // AttackNotify���� ȣ��
	void ReceiveInput(); // �޺� �Է� ����
    void OnAttackEnded();

protected:
    void ProceedCombo();		
    void PlayComboAttackMontage(int32 ComboIndex);


};
