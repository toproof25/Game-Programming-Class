// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerSpawner.generated.h"

UCLASS()
class TOONTANKS_API ATowerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerSpawner();

	// Tower 클래스 설정 에디터
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TSubclassOf<class ATower> Tower;

	// 난이도 상승 함수
	void AdjustSpawnRate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	float Difficulty = 1.f;

	// 스폰 속도  
	FTimerHandle FireRateTimerHandle;
	float SpawnRate = 3.f;
	float MinSpawnRate = 0.2f;

	// 월드에 스폰 함수 
	void WorldSpawnTower();

};
