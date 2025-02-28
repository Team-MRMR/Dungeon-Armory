// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EnemyBase.generated.h"

UCLASS()
class DUNGEON_ARMORY_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()


/***** Variables *****/
public:	
	/** AI가 경로를 순찰할 때 사용할 이동 타겟 포인트 */
	UPROPERTY(EditInstanceOnly, Category = "AI")
	TArray<AActor*> PatrolPoints;

/***** Functions *****/
public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
