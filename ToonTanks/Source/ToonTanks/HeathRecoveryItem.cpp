// Fill out your copyright notice in the Description page of Project Settings.


#include "HeathRecoveryItem.h"
#include "HealthComponent.h"
#include "Tank.h"

AHeathRecoveryItem::AHeathRecoveryItem()
{
    PrimaryActorTick.bCanEverTick = true; // Tick 활성화
}

void AHeathRecoveryItem::BeginPlay()
{
	Super::BeginPlay();
  //UE_LOG(LogTemp, Warning, TEXT("아이템 AHeathRecoveryItem"));
}

void AHeathRecoveryItem::Tick(float DeltaTime)
{
	RotationItem(); // 부모에서 정의한 회전 함수 호출
	//UE_LOG(LogTemp, Warning, TEXT("아이템 AttackPowerUpItem Tick 호출됨"));
}

// 체력 회복
void AHeathRecoveryItem::GetItem()
{
  if (Tank)
  {
    // Tank플레이어의 HealthComponent를 가져온다
    if (UHealthComponent* health = Cast<UHealthComponent>(Tank->FindComponentByClass<UHealthComponent>()))
    { 
      // HealthComponent에 있는 HealthRecovery(float value)함수를 통해 값을 넣어서 체력 회복
	    //UE_LOG(LogTemp, Warning, TEXT("체력 회복 ! AHeathRecoveryItem: %s"), *Tank->GetName());
      health->HealthRecovery(50.f);
      Destroy();
    }

  }
}