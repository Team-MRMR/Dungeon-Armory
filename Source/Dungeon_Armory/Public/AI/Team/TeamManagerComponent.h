// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AI/Team/TeamInfo.h"

#include "TeamManagerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_ARMORY_API UTeamManagerComponent : public UActorComponent
{
	GENERATED_BODY()

/*****Variables*****/  
private:  
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", meta = (AllowPrivateAccess = "true"))  
    TMap<ETeamType, FTeamRelation> TeamRelationMap;

/*****Functions*****/
public:	
	// Sets default values for this component's properties
    UTeamManagerComponent();

    UFUNCTION(BlueprintCallable, Category = "Team")
    // �� ���踦 �������� �Լ�
    ERelationType GetTeamRelationMap(ETeamType TeamA, ETeamType TeamB) const;

    UFUNCTION(BlueprintCallable, Category = "Team")
    // �� ���踦 �����ϴ� �Լ�
    void SetTeamRelationMap(ETeamType TeamA, ETeamType TeamB, ERelationType Releation);

protected:
    UFUNCTION(BlueprintCallable, Category = "Team")
    void InitializeTeamRelation();
};
