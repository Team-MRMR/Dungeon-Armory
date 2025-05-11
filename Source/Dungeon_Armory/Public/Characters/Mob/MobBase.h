// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Characters/Core/Interface/IDamageable.h"

#include "GenericTeamAgentInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "MobBase.generated.h"

class UCharacterStatComponent;
class UMobAttackComponent;
class UMovementControllerComponent;
class UTeamComponent;
class UBlackboardComponent;

class AAIController;

UCLASS()
class DUNGEON_ARMORY_API AMobBase : public ACharacter, public IGenericTeamAgentInterface, public IIDamageable
{
	GENERATED_BODY()

/***** Unreal *****/
public:
	AMobBase();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

/***** Stat *****/
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UCharacterStatComponent* StatComponent;

/***** Attack *****/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UMobAttackComponent* AttackComponent;

/***** Damage *****/
public:
	void ReceiveDamage(float DamageAmount) override;

/***** Movement *****/
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UMovementControllerComponent* MovementControllerComponent;

/***** Team *****/
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
	UTeamComponent* TeamComponent;

};
