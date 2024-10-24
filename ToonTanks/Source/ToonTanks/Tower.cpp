// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
	Super::BeginPlay();
	
  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}


void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (InFireRange())
    RotateTurret(Tank->GetActorLocation()); // 범위 내면 쫒아가기
}


void ATower::HandleDestruction()
{
	 // 효과 사운드
   Super::HandleDestruction();
   UE_LOG(LogTemp, Log, TEXT("Tower cpppppp 죽는단다낟나단다낟낟"));
   Destroy();
}


void ATower::CheckFireCondition()
{
  if (InFireRange())
    Fire(); // 공격
}

bool ATower::InFireRange() {
  if (Tank)
  {
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    if (Distance <= FireRange)
      return true;
  }
  return false;
}
