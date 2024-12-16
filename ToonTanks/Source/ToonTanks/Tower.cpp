// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
	Super::BeginPlay();
	
  // 플레이어 탱크를 변수에 저장 
  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  Speed = 1.f;

  // CheckFireCondition함수를 FireRate시간만큼 무한반복 
  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}


void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (!(Tank->bAlive))
  {
    return;
  }

  // 플레이어 방향으로 총구를 회전
  RotateTurret(Tank->GetActorLocation());

  // Tick마다 범위를 체크 
  if (!InFireRange())
  {
    // 공격 범위가 아니면 쫒아가기
    FollowPlayer();
  }

}

void ATower::FollowPlayer()
{
  // 방향 계산 (플레이어 위치 - 적 위치)
  FVector Direction = (Tank->GetActorLocation()) - GetActorLocation();

  // 방향 벡터 정규화
  FVector NormalizedDirection = Direction.GetSafeNormal();

  // 이동 벡터 계산 (정규화된 방향 * 속도)
  FVector Movement = NormalizedDirection * Speed;

  // 적의 새 위치 업데이트
  SetActorLocation(GetActorLocation() + Movement);
}

// 업그레이드 타워(난이도 상승)
void ATower::UpgradeTower(float Difficulty)
{
    // 공격력, 체력, 스피드, 공격속도 조정

    // AttackDamage = 10.f; // 공격력
    // Speed = 400.f; // 스피드
    // FireRate // 공격 속도
    // MaxHealth 최대 체력 

    GetWorldTimerManager().ClearTimer(FireRateTimerHandle); // 기존 타이머 중지
    AttackDamage *= Difficulty;
    Speed *= Difficulty;
    FireRate /= Difficulty;

    // 체력 컴포넌트 가져오기
    if (UHealthComponent* health = Cast<UHealthComponent>(FindComponentByClass<UHealthComponent>()))
    { 
      // 최대 체력 수정 
      health->MaxHealth *= Difficulty;

      // 최대 체력만큼 회복 - 회복을 통해 스폰 체력을 최대 체력으로 재설정
      health->HealthRecovery(health->MaxHealth);
    }

		if (FireRate <= MinFireRate)
		{
			FireRate = MinFireRate;
		}
    
	  //UE_LOG(LogTemp, Warning, TEXT("Tower! %f %f %f"), AttackDamage, Speed, FireRate);
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}



// 죽을 때 처리
void ATower::HandleDestruction()
{
	 // 효과 사운드
   Super::HandleDestruction();
   //UE_LOG(LogTemp, Log, TEXT("Tower cpppppp 죽는단다낟나단다낟낟"));
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
