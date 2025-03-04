// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "AI/Team/TeamInfo.h"

#include "TeamManager.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API UTeamManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
/*****Variables*****/
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", meta = (AllowPrivateAccess = "true"))
	TMap<ETeamType, FTeamRelation> TeamRelationMap;

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	static UTeamManager* GetInstance(UObject* WorldContextObject);

public:
	UFUNCTION(BlueprintCallable, Category = "Team")
	// 팀 관계를 가져오는 함수
	TMap<ETeamType, ERelationType> GetTeamRelation(ETeamType TeamA) const;

	UFUNCTION(BlueprintCallable, Category = "Team")
	// 팀 관계를 설정하는 함수
	void SetTeamRelation(ETeamType TeamA, ETeamType TeamB, ERelationType Releation);

protected:
	UFUNCTION(BlueprintCallable, Category = "Team")
	void InitializeTeamRelation();

};
