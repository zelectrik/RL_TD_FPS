// Fill out your copyright notice in the Description page of Project Settings.


#include "MechanicWeapon.h"
#include "Character/PlayableCharacter/BasicPlayerController.h"
#include "Camera/Shake/MyCameraShake.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AMechanicWeapon::AMechanicWeapon() : ABaseWeapon()
{
	m_SightDistance = 1000.0f;
	m_WeaponSpec = F_WeaponSpec();

	m_RemainingTimeToFire = 0.0f;
	m_RemainingAmmo = m_WeaponSpec.m_WeaponLoaderAmmo;

	m_RecoilShake = UMyCameraShake::StaticClass();

	const ConstructorHelpers::FObjectFinder<UMaterialInterface> BulletImpactDecal(TEXT("/Game/Materials/Development/Decal/Mat_D_BulletImpact.Mat_D_BulletImpact"));
	if (BulletImpactDecal.Succeeded()) {
		m_BulletHitDecal = BulletImpactDecal.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not find BulletImpactDecal."));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Could not find BulletImpactDecal."));
	}

	const ConstructorHelpers::FObjectFinder<UParticleSystem> BulletImpactParticle(TEXT("/Game/Particles/PS_test_Impact.PS_test_Impact"));
	if (BulletImpactParticle.Succeeded()) {
		m_BulletHitParticle = BulletImpactParticle.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not find BulletImpactParticle."));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Could not find BulletImpactParticle."));
	}

	
}

void AMechanicWeapon::Tick(float DeltaTime)
{
	if (b_IsShooting)
	{
		Firing();
	}
	m_RemainingTimeToFire -= DeltaTime;
}

E_OnFireResult AMechanicWeapon::Fire()
{
	if (m_RemainingAmmo <= 0)
	{
		return E_OnFireResult::VE_NoAmmo;
	}
	else if(m_RemainingTimeToFire > 0 && !m_WeaponSpec.b_AutomaticWeapon)
	{
		return E_OnFireResult::VE_FireRateNotReady;
	}
	else
	{
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
			//DrawDebugLine(GetWorld(), m_WeaponMesh->GetSocketLocation(FName("BulletSpawn")), m_WeaponMesh->GetSocketLocation(FName("BulletSpawn")) + GetBulletDirection()*m_SightDistance, FColor::Green, false, 5.0f);
			GetCharacterController()->ApplyRecoil(m_WeaponSpec.m_FireStrength, m_RecoilShake);
			FHitResult l_HitResult;
			ECollisionChannel l_CollisionChannel = ECollisionChannel();
			FCollisionQueryParams l_CollisionParams;
			l_CollisionParams.AddIgnoredActor(GetCharacterController()->GetPawn());
			l_CollisionParams.AddIgnoredActor(this);
			GetWorld()->LineTraceSingleByChannel(l_HitResult, m_WeaponMesh->GetSocketLocation(FName("BulletSpawn")), m_WeaponMesh->GetSocketLocation(FName("BulletSpawn")) + GetBulletDirection()*m_SightDistance, l_CollisionChannel, l_CollisionParams);
			if (l_HitResult.bBlockingHit)
			{
				OnBulletHit(l_HitResult);
			}
		}
		
		m_RemainingTimeToFire = m_WeaponSpec.m_FireRate;
		m_RemainingAmmo--;
	}
}

void AMechanicWeapon::OnBulletHit(FHitResult _HitResult)
{
	FTransform l_ParticleTransform = FTransform();
	l_ParticleTransform.SetLocation(_HitResult.ImpactPoint);
	l_ParticleTransform.SetRotation(FQuat(_HitResult.ImpactNormal.Rotation() + FRotator(-90, 0, 0)));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_BulletHitParticle, l_ParticleTransform);
	if (_HitResult.Actor->IsA(AStaticMeshActor::StaticClass()))
	{
		//UKismetMathLibrary::MakeRotFromX();
		ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(_HitResult.ImpactPoint, _HitResult.ImpactNormal.Rotation() + FRotator(90, 0, 0));

		UE_LOG(LogTemp, Warning, TEXT("Rotation : %s"), *_HitResult.ImpactNormal.Rotation().ToString());
		if (decal)
		{
			decal->SetDecalMaterial(m_BulletHitDecal);
			decal->SetLifeSpan(2.0f);
			
			decal->GetDecal()->FadeDuration = 2.0f;
			decal->GetDecal()->SetFadeScreenSize(0.f);
			decal->GetDecal()->bDestroyOwnerAfterFade = true;


			decal->GetDecal()->DecalSize = FVector(5.0f, 5.0f, 5.0f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No decal spawned"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *_HitResult.BoneName.ToString());
	}
}
