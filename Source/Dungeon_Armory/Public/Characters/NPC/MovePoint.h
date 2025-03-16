// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MovePoint.generated.h"

UCLASS()
class DUNGEON_ARMORY_API AMovePoint : public AActor
{
	GENERATED_BODY()
	
/***** Variables (Patrol) *****/
private:
	UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
	FVector PointLocation;

/***** Functions (Unreal) *****/
public:	
	AMovePoint();

protected:
	virtual void BeginPlay() override;

/***** Functions (Patrol) *****/
public:
	UFUNCTION(BlueprintCallable, Category = "Move")
	FVector GetPointLocation() const;

};
