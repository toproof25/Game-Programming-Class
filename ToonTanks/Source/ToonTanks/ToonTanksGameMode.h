// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual void BeginPlay() override;

	// 블루프린트에서 제어할 스타트게임 이벤트 설정 
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	// 블루프린트에서 제어할 게임오버 이벤트 설정 
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

};
