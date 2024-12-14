// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{

  // 죽은 액터가 플레이어 탱크라면
  if (DeadActor == Tank)
  {
    // 탱크의 HandleDestruction함수 실행
    Tank->HandleDestruction();

    if (ToonTanksPlayerController)
    {
      // 입력 비활성화화
      ToonTanksPlayerController->SetPlayerEnabledState(false);
      //Tank->DisableInput(Tank->GetTankPlayerController());
      //Tank->GetTankPlayerController()->bShowMouseCursor = false;
    }

    // 게임 오버 함수 실행 (블루프린트로 구성함)  
    GameOver(false);
  }

  // 죽은 액터가 적 터렛이라면 (cast로 가져오는데 못가져오면 null이므로 false, 가져오면 값이 있으므려 true)
  else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
  {
    
    // 적 터렛의 HandleDestruction를 실행
    UE_LOG(LogTemp, Log, TEXT("Tower gamemodemode 죽는단다낟나단다낟낟"));
    DestroyedTower->HandleDestruction();

    // 총 터렛 개수를 -1하고, 만일 0이라면 게임 종료
    if (--TargetTowers == 0)
    {
      GameOver(true);
    }
  }

}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

  // 게임 시작 시 HandleGameStart함수 실행
  HandleGameStart();
}


void AToonTanksGameMode::HandleGameStart()
{
  // 총 터렛의 수를 설정 
  TargetTowers = GetTargetTowerCount();

  // 플레이어 탱크를 설정 
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

  // 플레이어 컨트롤러를 바탕으로 AToonTanksPlayerController를 cast하여 설정 
  ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

  // 게임 시작  (블루프린트로 구성함) 
  StartGame();

  // ToonTanksPlayerController가 존재하면 
  if(ToonTanksPlayerController)
  {
    // 우선 플레이 입력 멈추기 
    ToonTanksPlayerController->SetPlayerEnabledState(false);

    // 타이머 지정
    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
      ToonTanksPlayerController,
      &AToonTanksPlayerController::SetPlayerEnabledState,
      true
    );
    // 타이머를 실행함 
    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
  }

}

// 적의 수를 반환
int32 AToonTanksGameMode::GetTargetTowerCount()
{
  // 터렛을 담는 배열
  TArray<AActor*> Towers;

  // GetAllActorsOfClass로 배열을 넘겨주고, 모든 러텟을 찾음
  UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

  // 터렛의 수를 반환
  return Towers.Num();
}