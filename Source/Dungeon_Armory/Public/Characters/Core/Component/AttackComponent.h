// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

class UAnimMontage;
class UCharacterStatComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

/***** Attack *****/
private:
    UPROPERTY(EditAnywhere, Category = "Attack")
    UAnimMontage* ComboAttackMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TArray<FName> ComboAttackSections;

    UPROPERTY()
    ACharacter* OwnerCharacter;

    UPROPERTY()
    UAnimInstance* AnimInstance;

    UPROPERTY()
    UCharacterStatComponent* StatComponent;

    int32 CurrentComboIndex;
    bool bIsAttacking;
    bool bCanNextCombo;

/***** Unreal *****/
public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

/***** Attack *****/
public:
    void StartAttack();     // �ܺο��� ���� ���� �� ȣ��
    void OnAttackHit();     // AttackNotify���� ȣ��
    void EnableCombo();     // AttackNotify���� ȣ��

protected:
    void TryCombo();
    void ProceedCombo();		
    void PlayComboAttackMontage(int32 ComboIndex);

    UFUNCTION()
    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);


};
