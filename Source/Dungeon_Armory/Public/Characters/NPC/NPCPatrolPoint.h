// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NPCPatrolPoint.generated.h"

UCLASS()
class DUNGEON_ARMORY_API ANPCPatrolPoint : public AActor
{
	GENERATED_BODY()
	
/***** Variables (Patrol) *****/
private:
	UPROPERTY(EditAnywhere, Category = "Patrol", meta = (AllowPrivateAccess = "true"))
	FVector PatrolLocation;

/***** Functions (Unreal) *****/
public:	
	ANPCPatrolPoint();

protected:
	virtual void BeginPlay() override;

/***** Functions (Patrol) *****/
public:
	UFUNCTION(BlueprintCallable, Category = "Patrol")
	FVector GetPatrolLocation() const;

};
