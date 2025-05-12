// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Item/Interface/IToolType.h"

#include "ToolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UToolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UToolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// --- 도구 관련 스탯 ---
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Efficiency;

private:
	void PerformByResourceType();

	FHitResult Hit;
	void DoLineTrace(FHitResult& HitResult);

};
