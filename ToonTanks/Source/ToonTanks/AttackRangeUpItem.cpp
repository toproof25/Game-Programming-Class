// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackRangeUpItem.h"
#include "Tank.h"

AAttackRangeUpItem::AAttackRangeUpItem()
{
    PrimaryActorTick.bCanEverTick = true; // Tick 활성화
}

void AAttackRangeUpItem::BeginPlay()
{
	Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("아이템 AttackRangeUpItem"));
}

void AAttackRangeUpItem::Tick(float DeltaTime)
{
	RotationItem(); // 부모에서 정의한 회전 함수 호출
	//UE_LOG(LogTemp, Warning, TEXT("아이템 AttackRangeUpItem Tick 호출됨"));
}

// 공격 범위 업그레이드
void AAttackRangeUpItem::GetItem()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackRangeUpItem ! : %s"), *Tank->GetName());
  if (Tank)
  {
    Tank->SetAttackRange(50.f);
    Destroy();
  }
}