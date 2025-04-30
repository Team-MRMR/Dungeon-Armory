// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPCPatrolPoint.h"

// Sets default values
ANPCPatrolPoint::ANPCPatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANPCPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
	PatrolLocation = GetActorLocation();  // 액터 위치 저장
}

FVector ANPCPatrolPoint::GetPatrolLocation() const
{
	return PatrolLocation;
}
