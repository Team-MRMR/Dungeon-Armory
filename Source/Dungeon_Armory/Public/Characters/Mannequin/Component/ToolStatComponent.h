// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToolStatComponent.generated.h"


//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS(abstract)
class DUNGEON_ARMORY_API UToolStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UToolStatComponent();

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
};
