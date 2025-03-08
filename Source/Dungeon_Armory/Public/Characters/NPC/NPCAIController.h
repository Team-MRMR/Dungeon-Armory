// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "NPCAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UTeamComponent;

UCLASS()
class DUNGEON_ARMORY_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	

/***** Variables *****/
protected:
    // AI ���� �ý��� (����: AIController���� ����)
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

	// �� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Team")
	UTeamComponent* TeamComponent;

private:
    // AI �ð� ���� ����
    UPROPERTY(VisibleAnywhere, Category = "Team")
	FGenericTeamId TeamId;

/***** Functions *****/
public:
    ANPCAIController();

    /** Retrieved owner attitude toward given Other object */
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    /** Retrieve team identifier in form of FGenericTeamId */
    virtual FGenericTeamId GetGenericTeamId() const override;

protected:
    virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
    // ���� ó�� �Լ�
    UFUNCTION()
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

};
