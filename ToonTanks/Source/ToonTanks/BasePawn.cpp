#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// 기본 생성자
ABasePawn::ABasePawn()
{
    // Tick() 함수 사용 
    PrimaryActorTick.bCanEverTick = true;

    // 캡슐 콜리젼을 루트 컴포넌트로 설정 
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComp;

    // 탱크 하체를 설정 - 캡슐 콜리션(부모) -> 탱크 하체(자식)
    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComp);

    // 탱크 상체를 설정 - 캡슐 콜리션(루트) -> 탱크 하체(부모) -> 탱크 상체(자식) 
    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    // 발사체 생성 위치 컴포넌트를 생성 
    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// LookAtTarget위치로 회전 
void ABasePawn::RotateTurret(FVector LookAtTarget)
{
    // 목표 위치 - 현재 위치 = 방향 
    FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

    // FRotator(Pitch, Yaw, Roll) - 목표 회전의 Yaw회전만 적용하여 회전값을 얻음 -> (0, 목표Yaw, 0)
    FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

    // RInterpTo(보간)을 통해 천천히 회전하도록 
    TurretMesh->SetWorldRotation(
        FMath::RInterpTo(
            TurretMesh->GetComponentRotation(),            // 현재 회전
            LookAtRotation,                                // 목표 회전
            UGameplayStatics::GetWorldDeltaSeconds(this),  // Delta Time
            5.f                                            // 보간 속도
        )
    );
}

// 파괴 시 동작 처리 -> 게임 모드 베이스 ActorDied에서 파괴된 액터를 체크한 후 실행
void ABasePawn::HandleDestruction()
{
    // TODO: 파괴 효과, 사운드, 파티클 등을 추가
    if(DeathParticles)
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
    }

    if(DeathSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}

    // 죽을 때 카메라 쉐이크 재생
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

// 스피드 value만큼 +
void ABasePawn::SetSpeed(float value)
{
    Speed += value;
}

// 공격력 증가
void ABasePawn::SetAttackDamage(float value)
{
    AttackDamage += value;
}


// 발사 함수 
void ABasePawn::Fire()
{
    // 발사체 스폰 위치 변수를 이용하여 위치, 회전을 가져온다 
    FVector Lotation = ProjectileSpawnPoint->GetComponentLocation();
    FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

    // 발사체를 SpawnActor로 (스폰할 클래스, 위치, 회전) 스폰한다 
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Lotation, Rotation);

    // 소유자를 스폰한 액터로 설정함 
    Projectile->SetOwner(this);

    // 디버그용으로 탄환 생성 위치에 구체를 그릴 수 있습니다 (주석 처리됨).
    // DrawDebugSphere(GetWorld(), Lotation, 25.f, 12, FColor::Blue, false, 3.f);
}
