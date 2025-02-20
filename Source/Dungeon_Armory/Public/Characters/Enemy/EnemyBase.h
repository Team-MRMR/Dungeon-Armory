// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

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
	/** AI의 현재 상태 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	EEnemyState CurrentState;

	/** AI가 경로를 순찰할 때 사용할 이동 타겟 포인트 */
	UPROPERTY(EditInstanceOnly, Category = "AI")
	TArray<AActor*> PatrolPoints;

	/** 플레이어 감지용 시야 체크 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UPawnSensingComponent* PawnSensingComponent;

private:
	// AI 감지 시스템
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

/***** Functions *****/
public:
	// Sets default values for this character's properties
	AEnemyBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** 상태 변경 함수 */
	void SetEnemyState(EEnemyState NewState);

	/** 플레이어 감지 함수 */
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	// 감지 처리 함수
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

};
