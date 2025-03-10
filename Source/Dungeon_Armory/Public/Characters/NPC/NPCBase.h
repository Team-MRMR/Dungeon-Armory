// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "AI/Team/TeamComponent.h"

#include "NPCBase.generated.h"

UCLASS()
class DUNGEON_ARMORY_API ANPCBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()


/***** Variables *****/
public:	
	/** Team Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team")
	UTeamComponent* TeamComponent;

private:
	/** AI�� ��θ� ������ �� ����� �̵� Ÿ�� ����Ʈ */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> PatrolPoints;

/***** Functions *****/
public:
	// Sets default values for this character's properties
	ANPCBase();

public:
	/** IGenericTeamAgentInterface implementation */
	virtual FGenericTeamId GetGenericTeamId() const override;

	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
