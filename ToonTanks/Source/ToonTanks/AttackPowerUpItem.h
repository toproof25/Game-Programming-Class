// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "AttackPowerUpItem.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AAttackPowerUpItem : public ABaseItem
{
	GENERATED_BODY()

	public:
		AAttackPowerUpItem();

	// Tick 함수 오버라이드
	virtual void Tick(float DeltaTime) override;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;


	private:
		// 부모 함수 오버라이드 
		void GetItem() override;
};
