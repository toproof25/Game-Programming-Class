// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
	Super::BeginPlay();
	
  // 플레이어 탱크를 변수에 저장 
  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

  // CheckFireCondition함수를 FireRate시간만큼 무한반복 
  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}


void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  // Tick마다 범위를 체크 
  if (InFireRange())
    RotateTurret(Tank->GetActorLocation()); // 범위 내면 쫒아가기
}


// 죽을 때 처리
void ATower::HandleDestruction()
{
	 // 효과 사운드
   Super::HandleDestruction();
   UE_LOG(LogTemp, Log, TEXT("Tower cpppppp 죽는단다낟나단다낟낟"));
   Destroy();
}

// 공격 범위라면 공격하는 함수 
void ATower::CheckFireCondition()
{
  if (Tank == nullptr)
  {
    return;
  }

  // 공격 범위 이면서, 플레이어가 살아있으면 
  if (InFireRange() && Tank->bAlive)
    Fire(); // 공격
}

// 범위 체크 
bool ATower::InFireRange() {
  if (Tank)
  {
    // 내 위치와, 상대 위치를 Dist으로 거리를 구함 
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    // 거리가 설정된 값 이하이면 
    if (Distance <= FireRange)
      return true;
  }
  return false;
}
