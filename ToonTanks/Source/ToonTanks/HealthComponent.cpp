// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// 현재 체력을 최대 체력으로
	Health = MaxHealth;

	// DamageTaken함수 OnTakeAnyDamage를 DamageTaken에 연결
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	// 게임 모드 베이스를 가져옴
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::HealthRecovery(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("HealthRecovery ! : %f"), Health);
	if (Health + value >= MaxHealth)
	{
		Health = MaxHealth;
	}
	else 
	{
		Health += value;
	}
	UE_LOG(LogTemp, Warning, TEXT("HealthRecovery ! : %f"), Health);

}


// 데미지를 입는 함수
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	// 현재 체력에 데미지를 적용용
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f %s ----"), Health, *DamagedActor->GetName());
	UE_LOG(LogTemp, Log, TEXT("Tower gamemodemode 죽는단다낟나단다낟낟 %s"), *DamagedActor->GetName());

	// 0이하가 된다면, 맞는 액터를 ActorDied함수 파라미터로 보낸다
	if (Health <= 0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}


