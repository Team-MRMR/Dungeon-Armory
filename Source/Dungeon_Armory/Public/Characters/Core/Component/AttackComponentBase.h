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

	int32 CurrentComboIndex; // 현재 콤보 인덱스

	bool bIsMontageEnded;   // 몽타주 종료 여부
	bool bCanReceiveInput;  // 콤보 입력 가능 여부
	bool bNextCombo;        // 다음 콤보 진행 여부

    FTimerHandle ComboInputTimerHandle;  // 콤보 지속시간 핸들러

/***** Unreal *****/
public:	
	// Sets default values for this component's properties
	UAttackComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

/***** Attack *****/
public:
    void StartAttack();     // 외부에서 공격 시작 시 호출
    void OnAttackHit();     // AttackNotify에서 호출
	void ReceiveInput(); // 콤보 입력 수신
    void OnAttackEnded();

protected:
    void ProceedCombo();		
    void PlayComboAttackMontage(int32 ComboIndex);


};
