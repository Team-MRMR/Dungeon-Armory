// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Manager/ManagerBase.h"
#include "GenericTeamAgentInterface.h"
#include "AI/Team/TeamInfo.h"

#include "TeamManager.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ARMORY_API UTeamManager : public UManagerBase
{
	GENERATED_BODY()
	
/***** Variables *****/
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", meta = (AllowPrivateAccess = "true"))
	TMap<ETeamType, FTeamRelation> TeamRelationMap;

/***** Functions (Unreal) *****/
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

/***** Functions (ManagerBase) *****/
public:
	static UTeamManager* GetInstance();

/***** Functions (Team) *****/
public:
	UFUNCTION(BlueprintCallable, Category = "Team")
	// ���� ��� ���� ���� �������� �Լ�
	TMap<ETeamType, ERelationType> GetTeamRelation(ETeamType TeamA) const;

	UFUNCTION(BlueprintCallable, Category = "Team")
	// ���� ��� ���� ���� �����ϴ� �Լ�
	void SetTeamRelation(ETeamType TeamA, ETeamType TeamB, ERelationType Releation);

	UFUNCTION(BlueprintCallable, Category = "Team")
	// ������ ���踦 �������� �Լ�
	ERelationType GetRelation(ETeamType TeamA, ETeamType TeamB) const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Team")
	void InitializeTeamRelationMap();

};
