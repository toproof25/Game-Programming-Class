// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpawner.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ATowerSpawner::ATowerSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

// Called every frame
void ATowerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void ATowerSpawner::BeginPlay()
{
	Super::BeginPlay();
	
  // CheckFireCondition함수를 FireRate시간만큼 무한반복 
  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATowerSpawner::WorldSpawnTower, SpawnRate, true);
}

// 월드에 적 스폰 함수 - 스폰하는 Tower마다 현재 Difficulty에 따라 UpgradeTower를 실행
void ATowerSpawner::WorldSpawnTower()
{
	if(Tower)
	{
		// 적 스폰 
		FVector SpawnerLocation = GetActorLocation();
		FVector location = FVector(SpawnerLocation.X, SpawnerLocation.Y, 84.f);
		AActor* tower = GetWorld()->SpawnActor<AActor>(Tower, location, FRotator::ZeroRotator);
		if (ATower* castedTower = Cast<ATower>(tower))
		{
			castedTower->UpgradeTower(Difficulty);
		}
	}
}

// 난이도 상승 - 스포너의 스폰 시간 단축 -> Difficulty 상승승
void ATowerSpawner::AdjustSpawnRate()
{
    // 타이머를 재설정하기 위한 절차
    GetWorldTimerManager().ClearTimer(FireRateTimerHandle); // 기존 타이머 중지
    SpawnRate = SpawnRate - SpawnRate * 0.1f;
		if (SpawnRate <= MinSpawnRate)
		{
			SpawnRate = MinSpawnRate;
		}
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATowerSpawner::WorldSpawnTower, SpawnRate, true); // 타이머 재설정
		Difficulty += 0.2f;
}




