// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedUpItem.h"
#include "Tank.h"


ASpeedUpItem::ASpeedUpItem()
{
    PrimaryActorTick.bCanEverTick = true; // Tick 활성화
}


void ASpeedUpItem::BeginPlay()
{
	Super::BeginPlay();
  //UE_LOG(LogTemp, Warning, TEXT("아이템 ASpeedUpItem"));
}

void ASpeedUpItem::Tick(float DeltaTime)
{
  RotationItem();
  //UE_LOG(LogTemp, Warning, TEXT("아이템 ASpeedUpItem"));
}

// Speed Up
void ASpeedUpItem::GetItem()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpeedUpItem ! 충돌한 액터: %s"), *Tank->GetName());
  if (Tank)
  {
    Tank->SetSpeed(10);
    Destroy();
  }
}