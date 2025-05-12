// Fill out your copyright notice in the Description page of Project Settings.


#include "GatherableActor/GatherableActor.h"

// Sets default values
AGatherableActor::AGatherableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGatherableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGatherableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGatherableActor::ReceiveDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0)
	{
		Die();
	}
}

void AGatherableActor::Die()
{
}

