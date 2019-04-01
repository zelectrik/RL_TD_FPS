// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "MechanicWeapon.generated.h"

//If you want this to appear in BP, make sure to use this instead
//USTRUCT(BlueprintType)
USTRUCT()
struct F_WeaponSpec
{
	GENERATED_BODY()

	UPROPERTY()
		int m_WeaponLoaderAmmo;

	UPROPERTY()
		float m_FireRate;

	UPROPERTY()
		float m_FireStrength;

	UPROPERTY()
		bool b_AutomaticWeapon;

	UPROPERTY()
		bool b_HitScan;

	//Constructor
	F_WeaponSpec()
	{
		m_FireStrength = 1;
		m_WeaponLoaderAmmo = 150;
		m_FireRate = 0.01f;
		b_AutomaticWeapon = true;
		b_HitScan = true;
	}
};

/**
 * 
 */
UCLASS()
class RL_TD_FPS_API AMechanicWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	AMechanicWeapon();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual E_OnFireResult Fire() override;

	UFUNCTION()
		virtual void StopFire() override;

	UFUNCTION()
		virtual E_OnReloadResult Reload() override;

protected:

	UPROPERTY()
		F_WeaponSpec m_WeaponSpec;

	UFUNCTION()
		void Firing();

private:
	float m_RemainingTimeToFire;

	float m_RemainingAmmo;

	bool b_IsShooting;
	
};
