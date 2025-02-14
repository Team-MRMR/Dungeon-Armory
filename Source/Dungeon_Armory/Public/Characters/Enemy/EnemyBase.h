// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle    UMETA(DisplayName = "Idle"),
	Patrol  UMETA(DisplayName = "Patrol"),
	Chase   UMETA(DisplayName = "Chase"),
	Return  UMETA(DisplayName = "Return")
};

UCLASS()
class DUNGEON_ARMORY_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()


/***** Variables *****/
public:	
	/** AI�� ���� ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	EEnemyState CurrentState;

	/** AI�� ��θ� ������ �� ����� �̵� Ÿ�� ����Ʈ */
	UPROPERTY(EditInstanceOnly, Category = "AI")
	TArray<AActor*> PatrolPoints;

	/** �÷��̾� ������ �þ� üũ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UPawnSensingComponent* PawnSensingComponent;


/***** Functions *****/
public:
	// Sets default values for this character's properties
	AEnemyBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** ���� ���� �Լ� */
	void SetEnemyState(EEnemyState NewState);

	/** �÷��̾� ���� �Լ� */
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
