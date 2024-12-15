// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Tank.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 탱크 하체를 설정 - 캡슐 콜리션(부모) -> 탱크 하체(자식)
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	RootComponent = ItemMesh;

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 탱크를 설정 
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// OnHit 함수 바인딩 -> ItemMesh에 충돌이 발생하면, OnHit 함수를 실행하라 
	ItemMesh->OnComponentHit.AddDynamic(this, &ABaseItem::OnHit);

	// 스폰폰시 파티클 재생
	if(SpawnParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, SpawnParticles, GetActorLocation(), GetActorRotation());
	}
	// 스폰폰시 사운드 재생
	if(SpawnSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation(), GetActorRotation());
	}

}

// 아이템을 일정 값만큼 회전하는 함수 
void ABaseItem::RotationItem()
{
	if (ItemMesh)
	{
		// 현재 회전 각도를 가져와서 Yaw에만 10도씩 추가
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw + 2.f, CurrentRotation.Roll);

		// 회전 값을 설정
		ItemMesh->SetWorldRotation(NewRotation);
	}
}

// 비활성화 된 Tick 
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 오버라이드 하여 각 아이템에서 사용한다.
void ABaseItem::GetItem()
{


}

// 아이템이 폰과 충돌할 때 무언가와 충돌할 때 발생 
void ABaseItem::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsGet) 
	{
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("아이템 OnHit!"));

	// 플레이어와 충돌하면 GetItem을 실행
	if (!bIsGet && OtherActor && OtherActor != this && OtherActor == Tank)
	{
    // OnHit시 파티클 재생ㄴ
		if(GetParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, GetParticles, GetActorLocation(), GetActorRotation());

		}

		// OnHit시 사운드 재생
		if(GetSound) 
		{
  		UGameplayStatics::PlaySoundAtLocation(this, GetSound, GetActorLocation(), GetActorRotation());
		}

		bIsGet = true;

		GetItem();
	}

}
