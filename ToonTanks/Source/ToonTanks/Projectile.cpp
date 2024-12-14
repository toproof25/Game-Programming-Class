// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "BasePawn.h"
#include "Tank.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"


// 생성자 
AProjectile::AProjectile()
{
 	// Tick()함수를 끔 (사용안함)
	PrimaryActorTick.bCanEverTick = false;

	// 설정된 변수에 발사체 메쉬를 넣고, 루트 컴포넌트로 설정함
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	// 설정된 변수에 발사체 이동 컴포넌트를 추가
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	// 시작 힘, 최대 스피드 설정 
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	// 변수에 파티클 설정  
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// 사운드가 존재하면 재생 - BeginPlay로 발사체가 스폰될 때 
	if(LaunchSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}

	// OnHit 함수 바인딩 -> ProjectileMesh에 충돌이 발생하면, OnHit 함수를 실행하라 
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

// 비활성화 된 Tick 
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 발사체가 무언가와 충돌할 때 발생 
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 발사체의 소유자를 가져옴 
	AActor* MyOwner = GetOwner();

	// 소유자가 없으면 자신 제거 
	if (MyOwner == nullptr) 
	{
		Destroy();
		return;	
	}


	// 탱크의 공격 수치를 가져옴 
	float AttackDamage = Cast<ABasePawn>(MyOwner)->AttackDamage;

	// 소유자의 컨트롤러를 가져옴 
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	// 피해 유형을 가져옴 -> 화염이냐 총알이냐 등 
	UClass* DamageTypeClass = UDamageType::StaticClass();

	// Hit액터가 존재하고, 자신이 아니면서, 내 소유자도 아닐 경우
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// Hit액터에게 피해를 적용 (누가 맞음?, 데미지, 누가 때림?, 뭐로 맞음?, 타박상이야 총상이야 뭐야) 
		UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, MyOwnerInstigator, this, DamageTypeClass);

		// OnHit시 파티클 재생
		if(HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		}

		// OnHit시 사운드 재생
		if(HitSound) 
		{
  		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
		}

		// OnHit시 카메라 쉐이크 재생
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}

	}
	Destroy();
}

