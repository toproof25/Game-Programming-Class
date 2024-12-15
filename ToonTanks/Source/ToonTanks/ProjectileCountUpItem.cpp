// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileCountUpItem.h"
#include "Tank.h"


AProjectileCountUpItem::AProjectileCountUpItem()
{
    PrimaryActorTick.bCanEverTick = true; // Tick 활성화
}

void AProjectileCountUpItem::BeginPlay()
{
	Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("아이템 ProjectileCountUpItem"));
}

void AProjectileCountUpItem::Tick(float DeltaTime)
{
	RotationItem(); // 부모에서 정의한 회전 함수 호출
	//UE_LOG(LogTemp, Warning, TEXT("아이템 ProjectileCountUpItem Tick 호출됨"));
}

// 발사 수 Up
void AProjectileCountUpItem::GetItem()
{
	UE_LOG(LogTemp, Warning, TEXT("ProjectileCountUpItem ! 충돌한 액터: %s"), *Tank->GetName());
  if (Tank)
  {
    Tank->SetProjectileCount(1);
    Destroy();
  }
}