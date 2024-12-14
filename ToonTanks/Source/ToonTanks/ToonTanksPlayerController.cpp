// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"


void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
  if (bPlayerEnabled)
  {
    // 플레이어 입력 활성화 
    GetPawn()->EnableInput(this);
  }
  else 
  {
    // 플레이어 입력 비활성화
    GetPawn()->DisableInput(this);
  }
  bShowMouseCursor = bPlayerEnabled;

}