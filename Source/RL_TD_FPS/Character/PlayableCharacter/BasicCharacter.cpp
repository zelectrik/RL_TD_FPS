// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "BasicPlayerController.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	m_FPSCamera->SetupAttachment(RootComponent);
	m_FPSCamera->bUsePawnControlRotation = true;

	GetMesh()->SetupAttachment(m_FPSCamera);

}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ABasicPlayerController* l_PlayerController = Cast<ABasicPlayerController>(GetController()))
	{
		l_PlayerController->InitializeController();
	}
}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

