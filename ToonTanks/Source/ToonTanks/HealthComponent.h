// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // 컴포넌트의 기본값을 설정합니다.
    UHealthComponent();

protected:
    // 게임 시작 시 호출되는 함수입니다.
    virtual void BeginPlay() override;

private:
    // 체력 (Blueprint에서 수정 가능)
    UPROPERTY(EditAnywhere)
    float MaxHealth = 100.f;

    // 현재 체력
    float Health = 0.f;

    // 데미지를 받았을 때 호출되는 함수 (Damage 이벤트에 바인딩) - 누가 맞았냐, 데미지 수치, 상처가 뭐냐(타박, 총알, 화염 등), 누가 때렸냐, 뭐로 맞았냐 
    UFUNCTION()
    void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

    // 게임 모드 베이스
    class AToonTanksGameMode* ToonTanksGameMode;

public:
    // 매 프레임마다 호출됩니다.
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
