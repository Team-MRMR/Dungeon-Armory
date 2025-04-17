// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/MovePoint.h"

// Sets default values
AMovePoint::AMovePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMovePoint::BeginPlay()
{
	Super::BeginPlay();
	
	PointLocation = GetActorLocation();  // ���� ��ġ ����
}

FVector AMovePoint::GetPointLocation() const
{
	return PointLocation;
}
