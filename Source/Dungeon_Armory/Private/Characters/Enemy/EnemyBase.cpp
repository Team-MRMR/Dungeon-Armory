// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

