// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AI/Team/TeamInfo.h"
#include "GenericTeamAgentInterface.h"

#include "TeamComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UTeamComponent : public UActorComponent, public IGenericTeamAgentInterface
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

    // IGenericTeamAgentInterface 구현 (AI Perception과 호환)
    virtual FGenericTeamId GetGenericTeamId() const override
    {
        return FGenericTeamId(static_cast<uint8>(TeamType));
    }

    UFUNCTION(BlueprintCallable, Category = "Team")
    ETeamType GetTeamType() const { return TeamType; }

    UFUNCTION(BlueprintCallable, Category = "Team")
    void SetTeamType(ETeamType NewTeamType) { TeamType = NewTeamType; }
};
