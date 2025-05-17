// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Characters/Mannequin/Interface/IToolEuipable.h"

#include "GatherComponent.generated.h"

class AGatherableActorBase;
class UAnimInstance;
class UAnimMontage;
class UCharacterStatComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UGatherComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGatherComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// --- �ִϸ��̼� ���� ---
public:
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* LoggingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* MiningMontage;

protected:
	UAnimInstance* AnimInstance;
	UCharacterStatComponent* Stat;

// --- ���� ���� ---
public:
	EToolType ToolType;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Distance")
	float GatheringDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Logging")
	float LoggingDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Logging")
	float LoggingStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Logging")
	float LoggingSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Logging")
	float LoggingEfficiency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Mining")
	float MiningDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Mining")
	float MiningStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Mining")
	float MiningSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Mining")
	float MiningEfficiency;

// --- �Է� ���� ---
private:
	bool bIsMontageEnded;		// ��Ÿ�ְ� �������� �Ǻ�
	bool bCanReceiveInput;		// �Է��� ���� �� �ִ��� �Ǻ�
	bool bHasNextGather;		// ���Է��� �ִ��� �Ǻ�

public:
	void StartGather();
	void OnGather();
	void OnGatherEnd();
	void ReceiveInput();

private:
	void DoLineTrace(FHitResult& HitResult);
	void UpdateToolType();

	void Logging();
	void Mining();

	void ProceedGather();
	void PlayGatherMontage();
};
