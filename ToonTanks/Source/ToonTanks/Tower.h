// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	

public:
	virtual void Tick(float DeltaTime) override;

	// 상속받은 함수 
	void HandleDestruction();
	
	void UpgradeTower(float value);

protected:
	virtual void BeginPlay() override;

private:
	// 플레이어 탱크
	class ATank* Tank;

	// 공격 범위 
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f;

  // 공격 속도 
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	float MinFireRate = 0.2f;
	void CheckFireCondition();



	// 공격 범위인지 체크하는 함수 
	bool InFireRange();

	// 공격 범위가 아니라면 플레이어에게 이동동
	void FollowPlayer();
};
