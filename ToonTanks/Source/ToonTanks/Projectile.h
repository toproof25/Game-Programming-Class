// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// 생성자
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	// 발사체 스태틱 메시
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	// 발사체 Projectile Movement Component 추가
	UPROPERTY(VisibleAnyWhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// OnHit 함수 추가 
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 데미지 설정 
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	// 파티클 (히트 발생하면면)
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticle;

	// 파티클 (날라갈 때)
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticles;

	// 사운드 (발사될 때)
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	// 사운드 (히트될 때)
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* HitSound;

	// 블루프린트 클래스 카메라 쉐이크를 변수로 설정정
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

};
