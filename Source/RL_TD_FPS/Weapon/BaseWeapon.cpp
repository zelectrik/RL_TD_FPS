// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Character/PlayableCharacter/BasicPlayerController.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	m_SightDistance = 10.f;

	// load Mesh
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Assets/SkeletalMesh/Weapon/BaseWeapon/BaseWeapon.BaseWeapon"));
	if (WeaponMesh.Succeeded()) {

		m_WeaponMesh->SetSkeletalMesh(WeaponMesh.Object);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not find weapon mesh."));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Could not find weapon mesh."));
	}

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FHitResult l_HitResult;
	//GetWorld()->LineTraceSingleByChannel(l_HitResult, m_WeaponMesh->GetSocketLocation(FName("BulletSpawn")), GetBulletDirection()*m_SightDistance, FColor::Green,
}

void ABaseWeapon::SetCharacterController(ABasicPlayerController* _controller)
{
	m_CharacterController = _controller;
}

E_OnFireResult ABaseWeapon::Fire()
{
	return E_OnFireResult();
}

void ABaseWeapon::StopFire()
{

}

E_OnReloadResult ABaseWeapon::Reload()
{
	return E_OnReloadResult();
}

FVector ABaseWeapon::GetBulletDirection()
{
	//Viewport Size
	if (GetCharacterController())
	{
		FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		FVector WorldLocation, WorldDirection;
		GetCharacterController()->DeprojectScreenPositionToWorld(ViewportSize.X / 2, ViewportSize.Y / 2, WorldLocation, WorldDirection);
		WorldLocation += WorldDirection * m_SightDistance;
		FVector Direction = WorldLocation - m_WeaponMesh->GetSocketLocation(FName("BulletSpawn"));
		Direction.Normalize();
		return Direction;
	}
	
	return FVector();
}

ABasicPlayerController * ABaseWeapon::GetCharacterController()
{
	return m_CharacterController;
}

