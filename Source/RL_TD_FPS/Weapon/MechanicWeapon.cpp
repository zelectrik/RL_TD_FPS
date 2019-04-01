// Fill out your copyright notice in the Description page of Project Settings.


#include "MechanicWeapon.h"
#include "Character/PlayableCharacter/BasicPlayerController.h"

AMechanicWeapon::AMechanicWeapon() : ABaseWeapon()
{
	m_SightDistance = 1000.0f;
	m_WeaponSpec = F_WeaponSpec();

	m_RemainingTimeToFire = 0.0f;
	m_RemainingAmmo = m_WeaponSpec.m_WeaponLoaderAmmo;
}

void AMechanicWeapon::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("DeltaTime : %f"), DeltaTime);
	if (b_IsShooting)
	{
		Firing();
	}
	m_RemainingTimeToFire -= DeltaTime;
}

E_OnFireResult AMechanicWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
	if (m_RemainingAmmo <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("b_IsShooting VE_NoAmmo"));
		return E_OnFireResult::VE_NoAmmo;
	}
	else if(m_RemainingTimeToFire > 0 && !m_WeaponSpec.b_AutomaticWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("b_IsShooting VE_FireRateNotReady"));
		return E_OnFireResult::VE_FireRateNotReady;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("b_IsShooting true"));
		b_IsShooting = true;
		return E_OnFireResult::VE_Success;
	}
	
}

void AMechanicWeapon::StopFire()
{
	b_IsShooting = false;
}

E_OnReloadResult AMechanicWeapon::Reload()
{
	return E_OnReloadResult();
}

void AMechanicWeapon::Firing()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
	if (m_RemainingAmmo <= 0)
	{
		b_IsShooting = false;
	}
	else if(m_RemainingTimeToFire <= 0)
	{

		if (!m_WeaponSpec.b_AutomaticWeapon)
		{
			b_IsShooting = false;
		}
		if (m_WeaponSpec.b_HitScan)
		{
			DrawDebugLine(GetWorld(), m_WeaponMesh->GetSocketLocation(FName("BulletSpawn")), m_WeaponMesh->GetSocketLocation(FName("BulletSpawn")) + GetBulletDirection()*m_SightDistance, FColor::Green, false, 5.0f);
			GetCharacterController()->ApplyRecoil(m_WeaponSpec.m_FireStrength);
		}
		
		m_RemainingTimeToFire = m_WeaponSpec.m_FireRate;
		m_RemainingAmmo--;
	}
}
