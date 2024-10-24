// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"


ATank::ATank()
{
  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  SpringArm->SetupAttachment(RootComponent);

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  if (TankPlayerController)
  { 
    FHitResult HitResult;
    TankPlayerController->GetHitResultUnderCursor(
      ECollisionChannel::ECC_Visibility,
      false,
      HitResult);

    RotateTurret(HitResult.ImpactPoint);
    //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
  }

}

void ATank::HandleDestruction()
{
	 // 효과 사운드
   Super::HandleDestruction();
   SetActorHiddenInGame(true);
   SetActorTickEnabled(false);
}




void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
  PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
  PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
  FVector DeltaLocation = FVector::ZeroVector;
  // 이동속도 = Director * Speed * Time
  DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
  AddActorLocalOffset(DeltaLocation, true);

  //UE_LOG(LogTemp, Warning, TEXT("DeltaLocation.X : %f, \t Value : %f"), DeltaLocation.X, Value);
}

void ATank::Turn(float Value)
{
  FRotator DeltaRotation = FRotator::ZeroRotator;
  // 회전 = TurnRate * Speed * Time
  DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
  AddActorLocalRotation(DeltaRotation, true);

}

