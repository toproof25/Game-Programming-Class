// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class TOONTANKS_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	// OnHit 함수 추가 
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 아이템 스태틱 매쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

	// 아이템 획득 파티클
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* SpawnParticles;

	// 아이템 먹을 때 파티클 
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* GetParticles;
	
	// 스폰 사운드 추가
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* SpawnSound;

	// 먹을 때 사운드 추가
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* GetSound;

	// 아이템 획득 여부
	bool bIsGet = false;


protected:

	// 아이템 얻을 시 - 각 아이템마다 오버라이드 해서 적용 
	virtual void GetItem();

	// 아이템 회전 함수 
	void RotationItem();

	// 플레이어 탱크 
	class ATank* Tank;

};

