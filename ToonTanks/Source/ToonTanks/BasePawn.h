// ABasePawn.h: ABasePawn 클래스의 헤더 파일로, 컴포넌트 및 함수 정의를 포함합니다.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
    GENERATED_BODY()

public:
    // 기본 생성자: Pawn의 기본 값을 설정합니다.
    ABasePawn();

    // 죽을 때 실행하는 함수 
    void HandleDestruction();

    // 발사체 클래스 설정 - TSubclassOf으로 설정하여 블루프린트에서 클래스 설정 
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<class AProjectile> ProjectileClass;

private:
    // 캡슐 형태의 콜리전을 생성 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UCapsuleComponent* CapsuleComp;

    // 탱크의 하체 부분 스태틱 매쉬 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BaseMesh;

    // 탱크의 상체 부분 스태틱 매쉬 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* TurretMesh;

    // 총알 생성 위치 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* ProjectileSpawnPoint;

    // 죽을 때 파티클
    UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;
    
    // 사운드 추가
    UPROPERTY(EditAnywhere, Category = "Combat")
    class USoundBase* DeathSound;

    // 블루프린트 클래스 카메라 쉐이크를 변수로 설정
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;


protected:
    // 터렛을 LookAtTarget 방향으로 회전 
    void RotateTurret(FVector LookAtTarget);

    // 발사체 발사 함수 
    void Fire();
};
