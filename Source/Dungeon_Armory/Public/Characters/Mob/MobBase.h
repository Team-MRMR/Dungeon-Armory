// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPC/NPCBase.h"
#include "MobBase.generated.h"

class UTeamComponent;

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API AMobBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
/***** Unreal *****/
public:
	AMobBase();

protected:
	virtual void BeginPlay() override;

/***** Team *****/
public:
	/** Team Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
	UTeamComponent* TeamComponent;

public:
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

/***** AI *****/

/***** Movement *****/
public:
	void ResetSpeed();
	void ApplySpeedModifier(float SpeedMultiplier, float Duration);
	void SetMovementSpeed(float NewSpeed);
};
