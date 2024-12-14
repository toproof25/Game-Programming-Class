// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPowerUpItem.h"
#include "Tank.h"


AAttackPowerUpItem::AAttackPowerUpItem()
{
    PrimaryActorTick.bCanEverTick = true; // Tick 활성화
}

void AAttackPowerUpItem::BeginPlay()
{
	Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("아이템 AttackPowerUpItem"));
}

void AAttackPowerUpItem::Tick(float DeltaTime)
{
	RotationItem(); // 부모에서 정의한 회전 함수 호출
	//UE_LOG(LogTemp, Warning, TEXT("아이템 AttackPowerUpItem Tick 호출됨"));
}

// 공격력 up
void AAttackPowerUpItem::GetItem()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackPowerUpItem ! 충돌한 액터: %s"), *Tank->GetName());
  if (Tank)
  {
    Tank->SetAttackDamage(10.0);
    Destroy();
  }
}