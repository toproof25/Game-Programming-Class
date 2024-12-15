// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerSpawner.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// 다른 외부에서 사용할 액터 사망 함수 설정 
	void ActorDied(AActor* DeadActor);


	// 현재 게임에서 킬 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Stats")
	int32 RemoveTowers = 0;

	// 현재까지 게임에서 최대 킬 수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Stats")
	int32 LoadRemoveTowers = 0;

private:
	// 플레이어 탱크 및 입력
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	// 시작 카운트 시간, 시작 함수 설정 
	float StartDelay = 3.f;
	void HandleGameStart();

	// 적 수, 수 구하는 함수 설정 
	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	// 스포너 수를 구함
	TArray<ATowerSpawner*> TowerSpawners;
	void GetTowerSpawerCount(TArray<ATowerSpawner*> &TowerSpawners);

	// 기타 필요한 함수들
	void SpawnRandomItem(const FVector& SpawnLocation);


protected:
	virtual void BeginPlay() override;

	// 블루프린트에서 제어할 스타트게임 이벤트 설정 
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	// 블루프린트에서 제어할 게임오버 이벤트 설정 
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	// 블루프린트에서 아이템 클래스를 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Classes")
	TArray<TSubclassOf<AActor>> ItemClasses;  // 아이템 클래스 배열
};
