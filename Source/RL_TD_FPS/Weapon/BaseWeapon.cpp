// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Public/Misc/MessageDialog.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	// load Mesh
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Assets/Mesh/Weapon/BaseWeapon/BaseWeapon.BaseWeapon"));
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

}

