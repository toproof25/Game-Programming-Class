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

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 기존 소유자 확인 로직 유지
    AActor* MyOwner = GetOwner();
    if (MyOwner == nullptr) 
    {
        Destroy();
        return;    
    }

    // 발사체가 hit된 위치를 기준으로 반경 500 범위에 데미지 적용
    if (OtherActor && OtherActor != this && OtherActor != MyOwner)
    {
        // 탱크의 공격 수치를 가져옴 
				if (ABasePawn* BasePawn = Cast<ABasePawn>(MyOwner))
				{
					float AttackDamage = BasePawn->AttackDamage;
					float AttackRange = BasePawn->AttackRange;

					// 소유자의 컨트롤러를 가져옴 
					AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

					TArray<AActor*> IgnoreActors;
					IgnoreActors.Add(MyOwner);  // MyOwner를 무시할 액터 리스트에 추가

					UGameplayStatics::ApplyRadialDamage(
							GetWorld(),                 // 월드
							AttackDamage,               // 데미지
							Hit.Location,               // 중심 위치 (hit 위치)
							AttackRange,                // 반경 
							UDamageType::StaticClass(), // 데미지 타입
							IgnoreActors,               // 무시할 액터들 (비워둠)
							this,                       // 원인 액터
							MyOwnerInstigator,          // 데미지 인스티게이터
							true                        // 모든 범위에 일정한 데미지 True
					);
					/*
						// 반경 범위 시각적으로 표시 (디버그 구)
						DrawDebugSphere(
								GetWorld(),                // 월드
								Hit.Location,              // 중심 위치
								AttackRange,               // 반경
								12,                        // 세그먼트 수 (구를 얼마나 부드럽게 그릴지)
								FColor::Red,               // 색상
								false,                     // 게임 플레이 중에 표시할지 여부 (false이면 디버그 모드에서만)
								3.0f                       // 선의 지속 시간 (초)
						);
					*/
					// 기존의 파티클, 사운드, 카메라 쉐이크 로직 유지
					if(HitParticle)
					{
							UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
					}

					if(HitSound) 
					{
							UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
					}

					if(HitCameraShakeClass)
					{
							GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
					}

				}

    }
    
    Destroy();
}

/*
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

		// Hit액터가 존재하고, 자신이 아니면서, 내 소유자도 아닐 경우
		if (OtherActor && OtherActor != this && OtherActor != MyOwner)
		{
			// 탱크의 공격 수치를 가져옴 
			float AttackDamage = Cast<ABasePawn>(MyOwner)->AttackDamage;

			// 소유자의 컨트롤러를 가져옴 
			AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

			// 피해 유형을 가져옴 -> 화염이냐 총알이냐 등 
			UClass* DamageTypeClass = UDamageType::StaticClass();

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
*/