// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MobBase.generated.h"

class UCharacterStatComponent;
class UTeamComponent;

UCLASS()
class DUNGEON_ARMORY_API AMobBase : public ACharacter
{
	GENERATED_BODY()

/***** Unreal *****/
public:
	AMobBase();

protected:
	virtual void BeginPlay() override;

/***** Team *****/
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UCharacterStatComponent* StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
	UTeamComponent* TeamComponent;

};
