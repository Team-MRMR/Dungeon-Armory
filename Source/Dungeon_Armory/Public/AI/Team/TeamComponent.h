// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AI/Team/TeamInfo.h"
#include "Manager/TeamManager.h"

#include "TeamComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UTeamComponent : public UActorComponent
{
	GENERATED_BODY()

/***** Variables ******/
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", meta = (AllowPrivateAccess = "true"))
	ETeamType TeamType;

/***** Functions *****/
public:	
	// Sets default values for this component's properties
	UTeamComponent();

    UFUNCTION(BlueprintCallable, Category = "Team")
	ETeamType GetTeamType() const { return TeamType; }

    UFUNCTION(BlueprintCallable, Category = "Team")
    void SetTeamType(const ETeamType NewTeamType) { TeamType = NewTeamType; }
};
